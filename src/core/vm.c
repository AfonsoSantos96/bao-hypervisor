/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>
#include <string.h>
#include <mem.h>
#include <mem_prot/mem.h>
#include <cache.h>
#include <config.h>

static void vm_master_init(struct vm* vm, const struct vm_config* config, vmid_t vm_id)
{
    vm->master = cpu()->id;
    vm->config = config;
    vm->cpu_num = config->platform.cpu_num;
    vm->id = vm_id;

    cpu_sync_init(&vm->sync, vm->cpu_num);

    vm_mem_prot_init(vm, config);
}

void vm_cpu_init(struct vm* vm)
{
    spin_lock(&vm->lock);
    vm->cpus |= (1UL << cpu()->id);
    spin_unlock(&vm->lock);
}

void vm_vcpu_init(struct vm* vm, const struct vm_config* config)
{
    size_t n = NUM_PAGES(sizeof(struct vcpu));
    size_t cpu_map_pos = cpu()->id;
    size_t cpu_mem_pos = 0;
    size_t vcpu_pos = 0;
    /*    Calculate vcpu offset from VM struct    */
    while (cpu_mem_pos < cpu_map_pos)
    {
        if((vm->cpus >> cpu_mem_pos) & 0x1) vcpu_pos++;
        cpu_mem_pos++;
    }

    struct vcpu* vcpu = 
        (struct vcpu*) (vm + sizeof(struct vm) + vcpu_pos*sizeof(struct vcpu));
    memset(vcpu, 0, n * PAGE_SIZE);

    cpu()->vcpu = vcpu;
    vcpu->phys_id = cpu()->id;
    vcpu->vm = vm;

    size_t count = 0, offset = 0;
    while (count < vm->cpu_num) {
        if (offset == cpu()->id) {
            vcpu->id = count;
            break;
        }
        if ((1UL << offset) & vm->cpus) {
            count++;
        }
        offset++;
    }

    vcpu_arch_init(vcpu, vm);
    vcpu_arch_reset(vcpu, config->entry);

    list_push(&vm->vcpu_list, &vcpu->node);
}

static void vm_update_as(struct vm* vm)
{
    vm->as.cpus = vm->cpus;
}

static void vm_copy_img_to_rgn(struct vm* vm, const struct vm_config* config,
                               struct vm_mem_region* reg)
{
    /* map original img address */
    size_t n_img = NUM_PAGES(config->image.size);
    struct ppages src_pa_img = mem_ppages_get(config->image.load_addr, n_img);
    vaddr_t src_va = src_pa_img.base;
    if(!vm_mem_region_is_phys(reg->place_phys)){
        src_va = mem_alloc_map(&cpu()->as, SEC_HYP_GLOBAL, &src_pa_img,
                                     NULL_VA, n_img, PTE_HYP_FLAGS);
    }
    if (src_va == NULL_VA) {
        ERROR("mem_alloc_map failed %s", __func__);
    }

    /* map new address */
    size_t offset = config->image.base_addr - reg->base;
    size_t dst_phys = reg->phys + offset;
    struct ppages dst_pp = mem_ppages_get(dst_phys, n_img);
    vaddr_t dst_va = mem_alloc_map(&cpu()->as, SEC_HYP_GLOBAL, &dst_pp,
                                     NULL_VA, n_img, PTE_HYP_FLAGS);
    if (dst_va == NULL_VA) {
        ERROR("mem_alloc_map failed %s", __func__);
    }

    memcpy((void*)dst_va, (void*)src_va, n_img * PAGE_SIZE);
    cache_flush_range((vaddr_t)dst_va, n_img * PAGE_SIZE);
    /*TODO: unmap */
}

void vm_map_mem_region(struct vm* vm, struct vm_mem_region* reg)
{
    size_t n = NUM_PAGES(reg->size);

    if (vm_mem_region_is_phys(reg->place_phys)) {
        struct ppages pa_reg = mem_ppages_get(reg->phys, n);        
        vaddr_t va = mem_alloc_map(&vm->as, SEC_VM_ANY, &pa_reg,
                    (vaddr_t)reg->base, n, PTE_VM_FLAGS);
        
        if (va != (vaddr_t)reg->base) {
            ERROR("failed to allocate vm's dev address");
        }   
    } else {
        vaddr_t va = mem_alloc_map(&vm->as, SEC_VM_ANY, NULL,
                    (vaddr_t)reg->base, n, PTE_VM_FLAGS);
        if (va != (vaddr_t)reg->base) {
            ERROR("failed to allocate vm's dev address");
        }
    }
}

static void vm_map_img_rgn_inplace(struct vm* vm, const struct vm_config* config,
                                   struct vm_mem_region* reg)
{
    /* mem region pages before the img */
    size_t n_before = (config->image.base_addr - reg->base) / PAGE_SIZE;
    /* pages after the img */
    size_t n_aft = ((reg->base + reg->size) -
                    (config->image.base_addr + config->image.size)) /
                   PAGE_SIZE;
    /* mem region pages for img */
    size_t n_img = NUM_PAGES(config->image.size);


    /* map img in place */
    struct ppages pa_img = mem_ppages_get(config->image.load_addr, n_img);

    vaddr_t va = mem_alloc_map(&vm->as, SEC_VM_ANY,
                            NULL, (vaddr_t)reg->base, n_before, PTE_VM_FLAGS);

    if (all_clrs(vm->as.colors)) {
        /* map img in place */
        mem_alloc_map(&vm->as, SEC_VM_ANY, &pa_img, va + n_before * PAGE_SIZE, n_img,
                PTE_VM_FLAGS);
        /* we are mapping in place, config is already reserved */
    } else {
        /* recolour img */
        mem_map_reclr(&vm->as, va + n_before * PAGE_SIZE, &pa_img, n_img,
                      PTE_VM_FLAGS);
    }
    /* map pages after img */
    mem_alloc_map(&vm->as, SEC_VM_ANY, NULL, va + (n_before + n_img) * PAGE_SIZE, n_aft,
            PTE_VM_FLAGS);
}

static void vm_install_image(struct vm* vm) {
    size_t img_num_pages = NUM_PAGES(vm->config->image.size);
    struct ppages img_ppages =
        mem_ppages_get(vm->config->image.load_addr, img_num_pages);
    vaddr_t src_va = mem_alloc_map(&cpu()->as, SEC_HYP_GLOBAL, &img_ppages,
        NULL_VA, img_num_pages, PTE_HYP_FLAGS);
    vaddr_t dst_va = mem_map_cpy(&vm->as, &cpu()->as, vm->config->image.base_addr,
                                NULL_VA, img_num_pages);
    memcpy((void*)dst_va, (void*)src_va, vm->config->image.size);
    cache_flush_range((vaddr_t)dst_va, vm->config->image.size);
    mem_unmap(&cpu()->as, src_va, img_num_pages, false);
    mem_unmap(&cpu()->as, dst_va, img_num_pages, false);
}

static void vm_map_img_rgn(struct vm* vm, const struct vm_config* config,
                           struct vm_mem_region* reg)
{
    if (vm_mem_region_is_phys(reg->place_phys)) {
        vm_copy_img_to_rgn(vm, config, reg);
        vm_map_mem_region(vm, reg);
    } else if(config->image.inplace) {
        vm_map_img_rgn_inplace(vm, config, reg);
    } else {
        vm_map_mem_region(vm, reg);
        vm_install_image(vm);
    }
}

static void vm_init_mem_regions(struct vm* vm, const struct vm_config* config)
{
    for (size_t i = 0; i < config->platform.region_num; i++) {
        struct vm_mem_region* reg = &config->platform.regions[i];
        bool img_is_in_rgn = range_in_range(
            config->image.base_addr, config->image.size, reg->base, reg->size);
        if (img_is_in_rgn) {
            vm_map_img_rgn(vm, config, reg);
        } else {
            vm_map_mem_region(vm, reg);
        }
    }
}

static void vm_init_ipc(struct vm* vm, const struct vm_config* config)
{
    vm->ipc_num = config->platform.ipc_num;
    vm->ipcs = config->platform.ipcs;
    for (size_t i = 0; i < config->platform.ipc_num; i++) {
        struct ipc *ipc = &config->platform.ipcs[i];
        struct shmem *shmem = ipc_get_shmem(ipc->shmem_id);
        if(shmem == NULL) {
            WARNING("Invalid shmem id in configuration. Ignored.");
            continue;
        }
        size_t size = ipc->size;
        if(ipc->size > shmem->size) {
            size = shmem->size;
            WARNING("Trying to map region to smaller shared memory. Truncated");
        }
        
        spin_lock(&shmem->lock);
        shmem->cpu_masters |= (1ULL << cpu()->id);
        spin_unlock(&shmem->lock);

        struct vm_mem_region reg = {
            .base = ipc->base,
            .size = size,
            .place_phys = true,
            .phys = shmem->phys,
            .colors = shmem->colors
        };

        vm_map_mem_region(vm, &reg);
    }
}

static void vm_init_dev(struct vm* vm, const struct vm_config* config)
{
    for (size_t i = 0; i < config->platform.dev_num; i++) {
        struct vm_dev_region* dev = &config->platform.devs[i];

        size_t n = ALIGN(dev->size, PAGE_SIZE) / PAGE_SIZE;

        if (dev->va != NULL_VA) {
            mem_alloc_map_dev(&vm->as, SEC_VM_ANY, (vaddr_t)dev->va, dev->pa, n);
        }

        for (size_t j = 0; j < dev->interrupt_num; j++) {
            interrupts_vm_assign(vm, dev->interrupts[j]);
        }
    }

    if (io_vm_init(vm, config)) {
        for (size_t i = 0; i < config->platform.dev_num; i++) {
            struct vm_dev_region* dev = &config->platform.devs[i];
            if (dev->id) {
                if(!io_vm_add_device(vm, dev->id)){
                    ERROR("Failed to add device to iommu");
                }
            }
        }
    }
      
}

void vm_init(struct vm* vm, const struct vm_config* config, bool master, vmid_t vm_id)
{
    /**
     * Before anything else, initialize vm structure.
     */
    if (master) {
        vm_master_init(vm, config, vm_id);
    }

    /*
     *  Initialize each core.
     */
    vm_cpu_init(vm);

    cpu_sync_barrier(&vm->sync);
    //cpu_sync_memprot();

    /*
     *  Update VM AS cpu bitmap with VM cpu affinity.
     */
    if (master) {
        vm_update_as(vm);
    }

    /*
     *  Initialize each virtual core.
     */
    vm_vcpu_init(vm, config);

    cpu_sync_barrier(&vm->sync);
    //cpu_sync_memprot();

    /**
     * Perform architecture dependent initializations. This includes,
     * for example, setting the page table pointer and other virtualization
     * extensions specifics.
     */
    vm_arch_init(vm, config);

    /**
     * Create the VM's address space according to configuration and where
     * its image was loaded.
     */
    if (master) {
        vm_init_mem_regions(vm, config);
        vm_init_dev(vm, config);
        vm_init_ipc(vm, config);
    }

    cpu_sync_barrier(&vm->sync);
    //cpu_sync_memprot();
}

struct vcpu* vm_get_vcpu(struct vm* vm, vcpuid_t vcpuid)
{
    list_foreach(vm->vcpu_list, struct vcpu, vcpu)
    {
        if (vcpu->id == vcpuid) return vcpu;
    }

    return NULL;
}

void vm_emul_add_mem(struct vm* vm, struct emul_mem* emu)
{
    list_push(&vm->emul_mem_list, &emu->node);
}

void vm_emul_add_reg(struct vm* vm, struct emul_reg* emu)
{
    list_push(&vm->emul_reg_list, &emu->node);
}    

emul_handler_t vm_emul_get_mem(struct vm* vm, vaddr_t addr)
{
    emul_handler_t handler = NULL;
    list_foreach(vm->emul_mem_list, struct emul_mem, emu) {
        if (addr >= emu->va_base && (addr < (emu->va_base + emu->size))) {
            handler = emu->handler;
            break;
        }
    }

    return handler;
}

emul_handler_t vm_emul_get_reg(struct vm* vm, vaddr_t addr)
{
    emul_handler_t handler = NULL;
    list_foreach(vm->emul_reg_list, struct emul_reg, emu) {
        if(emu->addr == addr) {
            handler = emu->handler;
            break; 
        }
    }

    return handler;
}

void vm_msg_broadcast(struct vm* vm, struct cpu_msg* msg)
{
    for (size_t i = 0, n = 0; n < vm->cpu_num - 1; i++) {
        if (((1U << i) & vm->cpus) && (i != cpu()->id)) {
            n++;
            cpu_send_msg(i, msg);
        }
    }
}

__attribute__((weak)) cpumap_t vm_translate_to_pcpu_mask(struct vm* vm,
                                                         cpumap_t mask,
                                                         size_t len)
{
    cpumap_t pmask = 0;
    cpuid_t shift;
    for (size_t i = 0; i < len; i++) {
        if ((mask & (1ULL << i)) &&
            ((shift = vm_translate_to_pcpuid(vm, i)) != INVALID_CPUID)) {
            pmask |= (1ULL << shift);
        }
    }
    return pmask;
}

__attribute__((weak)) cpumap_t vm_translate_to_vcpu_mask(struct vm* vm,
                                                         cpumap_t mask,
                                                         size_t len)
{
    cpumap_t pmask = 0;
    vcpuid_t shift;
    for (size_t i = 0; i < len; i++) {
        if ((mask & (1ULL << i)) &&
            ((shift = vm_translate_to_vcpuid(vm, i)) != INVALID_CPUID)) {
            pmask |= (1ULL << shift);
        }
    }
    return pmask;
}

void vcpu_run(struct vcpu* vcpu)
{
    cpu()->vcpu->active = true;
    vcpu_arch_run(vcpu);
}
