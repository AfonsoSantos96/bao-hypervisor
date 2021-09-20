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

#ifndef __STRING_H_
#define __STRING_H_

#include <bao.h>

<<<<<<< HEAD
#define WORD_TYPE unsigned long
#define WORD_SIZE (sizeof(WORD_TYPE *))

void *memcpy(void *dst, const void *src, unsigned int count);
void *memset(void *dest, unsigned int c, unsigned int count);

char *strcat(char *dest, char *src);
unsigned int strlen(const char *s);
unsigned int strnlen(const char *s, size_t n);
=======
void *memcpy(void *dst, const void *src, size_t count);
void *memset(void *dest, uint8_t c, size_t count);

char *strcat(char *dest, char *src);
size_t strlen(const char *s);
size_t strnlen(const char *s, size_t n);
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
char *strcpy(char *dest, char *src);

#endif /* __STRING_H_ */
