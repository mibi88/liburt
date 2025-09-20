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

#include <int/div.h>

int __divsi3(int a, int b) {
    URT_DIV(int, a, b);
}

long __divdi3(long a, long b) {
    URT_DIV(long, a, b);
}

unsigned int __udivsi3(unsigned int a, unsigned int b) {
    URT_UDIV(int, a, b);
}

unsigned long __udivdi3(unsigned long a, unsigned long b) {
    URT_UDIV(long, a, b);
}

unsigned long __udivmoddi4(unsigned long a, unsigned long b,
                           unsigned long *c) {
    unsigned long q = 0;
    unsigned long r = 0;

    if(!(b)) abort();

    _URT_UDIV(long, a, b, q, r);

    *c = r;
    return q;
}

#if URT_NONANSI

long long __divti3(long long a, long long b) {
    URT_DIV(long long, a, b);
}

unsigned long long __udivti3(unsigned long long a, unsigned long long b) {
    URT_UDIV(long long, a, b);
}

unsigned long long __udivmodti4(unsigned long long a, unsigned long long b,
                                unsigned long long *c) {
    unsigned long long q = 0;
    unsigned long long r = 0;

    if(!(b)) abort();

    _URT_UDIV(long long, a, b, q, r);

    *c = r;
    return q;
}

#endif
