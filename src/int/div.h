/* liburt: Highly portable drop-in replacement for libgcc or compiler-rt.
 * by Mibi88
 *
 * This software is licensed under the BSD-3-Clause license:
 *
 * Copyright 2025 Mibi88
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef URT_DIV_H
#define URT_DIV_H

#if URT_HAS_LIBC
#include <stdlib.h>
#else
#include <stddef.h>

#define abort() *(volatile unsigned char*)NULL = 1
#endif

#include <limits.h>

#define URT_ABS(x) ((x) < 0 ? -(x) : (x))
#define URT_LXOR(a, b) (!((a) && (b)) && ((a) || (b)))
#define URT_QNEG(a, b) URT_LXOR(a < 0, b < 0)

/* TODO: Use a more efficient algorithm */
#define _URT_UDIV(type, a, b, q, r) \
    { \
        size_t n = CHAR_BIT*sizeof(type)+1; \
        for(;--n;){ \
            r <<= 1; \
            r |= (a>>(CHAR_BIT*sizeof(type)-1)); \
            if(r >= b){ \
                r -= b; \
                q |= (unsigned type)1<<(n-1); \
            } \
            a <<= 1; \
        } \
    }

#define URT_DIV(type, a, b) \
    { \
        unsigned type _a = URT_ABS(a); \
        unsigned type _b = URT_ABS(b); \
        unsigned type q = 0; \
        unsigned type r = 0; \
 \
        if(!(b)) abort(); \
 \
        _URT_UDIV(type, _a, _b, q, r); \
        if(URT_QNEG(a, b)) return -q; \
 \
        return q; \
    }

#define URT_UDIV(type, a, b) \
    { \
        unsigned type q = 0; \
        unsigned type r = 0; \
 \
        if(!(b)) abort(); \
 \
        _URT_UDIV(type, a, b, q, r); \
 \
        return q; \
    }

#endif
