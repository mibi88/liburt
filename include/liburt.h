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

#ifndef LIBURT_H
#define LIBURT_H

int __mulsi3(int a, int b);
long __muldi3(long a, long b);

int __ashlsi3(int a, int b);
long __ashldi3(long a, long b);
int __ashrsi3(int a, int b);
long __ashrdi3(long a, long b);
int __lshrsi3(int a, int b);
long __lshrdi3(long a, long b);

int __divsi3(int a, int b);
long __divdi3(long a, long b);

unsigned int __udivsi3(unsigned int a, unsigned int b);
unsigned long __udivdi3(unsigned long a, unsigned long b);
unsigned long __udivmoddi4(unsigned long a, unsigned long b,
                           unsigned long *c);

int __modsi3(int a, int b);
long __moddi3(long a, long b);

unsigned int __umodsi3(unsigned int a, unsigned int b);
unsigned long __umoddi3(unsigned long a, unsigned long b);

int __mulsi3(int a, int b);
long __muldi3(long a, long b);

int __mulvsi3(int a, int b);
int __mulvdi3(long a, long b);

long __negdi2(long a);

#if URT_NONANSI
#include <stdint.h>

/* TODO: Choose a more appropriate type. */
typedef void UBILtype;

long long __multi3(long long a, long long b);

long long __ashlti3(long long a, long long b);
long long __ashrti3(long long a, long long b);
long long __lshrti3(long long a, long long b);

long long __divti3(long long a, long long b);

unsigned long long __udivti3(unsigned long long a, unsigned long long b);

unsigned long long __udivmodti4(unsigned long long a, unsigned long long b,
                                unsigned long long *c);

long long __modti3(long long a, long long b);
unsigned long long __umodti3(unsigned long long a, unsigned long long b);


long long __multi3(long long a, long long b);
void __mulbitint3(UBILtype *ret, int32_t retprec, const UBILtype *u,
                  int32_t uprec, const UBILtype *v, int32_t vprec);

long long __negti2(long long a);
#endif

#endif
