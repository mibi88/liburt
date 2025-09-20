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

#include <int/shift.h>

/* Left shift */
int __ashlsi3(int a, int b) {
    URT_SHIFT_LEFT(a, b);
}

long __ashldi3(long a, long b) {
    URT_SHIFT_LEFT(a, b);
}

/* Arithmetic shift to the right */
int __ashrsi3(int a, int b) {
    URT_SHIFT_RIGHT(a, b);
}

long __ashrdi3(long a, long b) {
    URT_SHIFT_RIGHT(a, b);
}

/* Logical shift to the right */
int __lshrsi3(int a, int b) {
    URT_LSHIFT_RIGHT(int, a, b);
}

long __lshrdi3(long a, long b) {
    URT_LSHIFT_RIGHT(long, a, b);
}

#if URT_NONANSI

/* Left shift */
long long __ashlti3(long long a, long long b) {
    unsigned long _a = a;
    unsigned long _b = b;
    URT_SHIFT_LEFT(_a, _b);
}

/* Arithmetic shift to the right */
long long __ashrti3(long long a, long long b) {
    URT_SHIFT_RIGHT(a, b);
}

/* Logical shift to the right */
long long __lshrti3(long long a, long long b) {
    URT_LSHIFT_RIGHT(long long, a, b);
}

#endif
