/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <bitmap.h>

<<<<<<< HEAD
long bitmap_find_nth(bitmap_t map, long size, long nth, long start,
=======
ssize_t bitmap_find_nth(bitmap_t* map, size_t size, size_t nth, size_t start,
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
                        bool set)
{
    if (size <= 0 || nth <= 0 || start < 0) return -1;

    size_t count = 0;
<<<<<<< HEAD
    size_t bit = set ? 1 : 0;
=======
    unsigned bit = set ? 1 : 0;
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

    for (ssize_t i = start; i < size; i++) {
        if (bitmap_get(map, i) == bit) {
            if (++count == nth) return i;
        }
    }

    return -1;
}

size_t bitmap_count_consecutive(bitmap_t* map, size_t size, size_t start,
                                size_t n)
{
    if (n <= 1) return n;

<<<<<<< HEAD
    unsigned char b = bitmap_get(map, start);
=======
    unsigned b = bitmap_get(map, start);
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff
    size_t count = 1;
    start += 1;

    while (start < size) {
        if (bitmap_get(map, start) == b)
            count++;
        else
            break;
        if (count == n) break;
        start++;
    }

    return count;
}

<<<<<<< HEAD
long bitmap_find_consec(bitmap_t map, size_t size, size_t start, size_t n,
                            bool set)
{
    size_t count = 0;
    long i = 0;
=======
ssize_t bitmap_find_consec(bitmap_t* map, size_t size, size_t start, size_t n,
                            bool set)
{
    ssize_t count = 0;
    ssize_t i = 0;
>>>>>>> ca07723b54d7f114fbb3c0808b4d27e48badf6ff

    // find first set
    if ((i = bitmap_find_nth(map, size, 1, start, set)) < 0) return -1;

    while (i < size) {
        // find the last (with n as maximum) contiguous set page
        count = bitmap_count_consecutive(map, size, i, n);
        if (count < n) {  // if didn't found enough n contiguous set pages
            i += count;
            // find the last contiguous ~set page
            i += bitmap_count_consecutive(map, size, i, -1);
        } else {
            break;
        }
    }

    if (i >= size) i = -1;

    return i;
}
