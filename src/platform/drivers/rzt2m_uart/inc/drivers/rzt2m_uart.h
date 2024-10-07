/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef UART_RENESAS_H
#define UART_RENESAS_H

#include <stdint.h>
#include <stdbool.h>
#include "drivers/uart_api.h"
#include "drivers/renesas.h"

#include "drivers/bsp_clk.h"
#include "drivers/bsp_ioport_api.h"


typedef R_SCI0_Type bao_uart_t;


#define serial_puts(str_buffer) uart_puts(1,str_buffer) 
#define serial_getc(str_buffer) uart_getc(1) 


void renesas_uart_init(volatile R_SCI0_Type * const p_api_ctrl, uart_cfg_t const * const p_cfg);

void uart_init(volatile R_SCI0_Type * const p_api_ctrl);

void uart_start(volatile  R_SCI0_Type * const p_api_ctrl, uart_cfg_t const * const p_cfg);

void uart_read(volatile R_SCI0_Type * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
void uart_write(volatile R_SCI0_Type * const p_api_ctrl, int8_t const * const p_src);


void uart_putc(volatile R_SCI0_Type * ptr_uart, int8_t c);
void uart_puts(volatile R_SCI0_Type * ptr_uart, const int8_t *s);

uint32_t uart_getc(volatile R_SCI0_Type * p_uart);




void uart_disable(volatile R_SCI0_Type * const p_api_ctrl);
void uart_enable(volatile R_SCI0_Type * const p_api_ctrl);


void uart_set_baud_rate(R_SCI0_Type * const p_api_ctrl, uint32_t baud_rate);
void renesas_set_baud_rate(volatile  R_SCI0_Type * const p_api_ctrl, void const * const p_baud_setting);



#endif
