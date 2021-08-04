/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Sandro Pinto <sandro.pinto@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <string.h>

void *memcpy(void *dst, const void *src, unsigned int count)
{
    int i;
    unsigned char *dst_tmp = dst;
    const unsigned char *src_tmp = src;

    if (!((WORD_TYPE)src & (WORD_SIZE - 1)) &&
        !((WORD_TYPE)dst & (WORD_SIZE - 1))) {
        for (i = 0; i < count; i += WORD_SIZE) {
            if (i + (WORD_SIZE - 1) > count - 1) break;
            *(WORD_TYPE *)dst_tmp = *(WORD_TYPE *)src_tmp;
            dst_tmp += WORD_SIZE;
            src_tmp += WORD_SIZE;
        }
        if (i <= count - 1) {
            for (; i < count; i++) {
                *dst_tmp = *src_tmp;
                dst_tmp++;
                src_tmp++;
            }
        }
    } else {
        for (i = 0; i < count; i++) dst_tmp[i] = src_tmp[i];
    }
    return dst;
}

void *memset(void *dest, unsigned int c, unsigned int count)
{
    unsigned char *d;
    d = (unsigned char *)dest;

    while (count--) {
        *d = c;
        d++;
    }

    return dest;
}

char *strcat(char *dest, char *src)
{
    char *save = dest;

    for (; *dest; ++dest);
    while ((*dest++ = *src++) != 0);

    return (save);
}

unsigned int strlen(const char *s)
{
    const char *sc;
    for (sc = s; *sc != '\0'; ++sc) {
        /* Just iterate */
    }
    return sc - s;
}

unsigned int strnlen(const char *s, size_t n)
{
    const char *str;

    for (str = s; *str != '\0' && n--; ++str) {
        /* Just iterate */
    }
    return str - s;
}

char *strcpy(char *dest, char *src)
{
    char *tmp = dest;

    while ((*dest++ = *src++) != '\0') {
        /* Just iterate */
    }
    return tmp;
}

unsigned int strcmp(char *str0, char *str1)
{
    char *tmp0 = str0, *tmp1 = str1;

    while (*tmp0 == *tmp1 && ((*tmp0 != '\0') && (*tmp1 != '\0'))) {
        tmp0++;
        tmp1++;
    }

    return (unsigned int)(tmp0 != tmp1);
}
