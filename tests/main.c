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

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <getopt.h>

#include <liburt.h>

#include <limits.h>

static const char help_str[] = (
    "USAGE: %s [-h]\n"
    "liburt test tool\n"
    "\n"
    "Options:\n"
    "  -h   Show this help message\n"
);

#if URT_NONANSI
typedef long long imax_t;
typedef unsigned long long umax_t;
#else
typedef long imax_t;
typedef unsigned long umax_t;
#endif

#define TEST(type, format, name, cmp) \
    { \
        type r = 0; \
        puts("|  Testing " #cmp "..."); \
        if(cmp){ \
            puts("|   +-> Test passed!"); \
        }else{ \
            fprintf(stderr, \
                    "|   +-> Test failed! " #name " needs to be fixed!\n"\
                    "+-> Return value: " format "\n", r); \
            exit(EXIT_FAILURE); \
        } \
    }

#define ASHL(l) __ashl##l##i3
#define ASHR(l) __ashr##l##i3
#define LSHR(l) __lshr##l##i3

#define SHIFT_TESTS(l, f, type) \
    { \
        TEST(type, f, ASHL(l), (r = ASHL(l)(3, 4)) == 48); \
        TEST(type, f, ASHL(l), !(r = ASHL(l)(3, type##_bits))); \
        TEST(type, f, ASHL(l), (r = ASHL(l)(3, 0)) == 3); \
        TEST(type, f, ASHR(l), (r = ASHR(l)(ASHL(l)(3, type##_bits-2), \
                                                  type##_bits-2)) == -1); \
        TEST(type, f, ASHR(l), (r = ASHR(l)(5, 1)) == 2); \
        TEST(type, f, LSHR(l), (r = LSHR(l)(ASHL(l)(3, type##_bits-2), \
                                                  type##_bits-2)) == 3); \
        TEST(type, f, LSHR(l), (r = LSHR(l)(5, 1)) == 2); \
    }

#define MUL(l) __mul##l##i3

#define MUL_TESTS(l, f, type) \
    { \
        TEST(type, f, MUL(l), !(r = MUL(l)(3, 0))); \
        TEST(type, f, MUL(l), !(r = MUL(l)(0, 3))); \
        TEST(type, f, MUL(l), !(r = MUL(l)(0, 0))); \
        TEST(type, f, MUL(l), (r = MUL(l)(439, 56)) == 24584); \
        TEST(type, f, MUL(l), (r = MUL(l)(23, -98)) == -2254); \
        TEST(type, f, MUL(l), (r = MUL(l)(-48, 37)) == -1776); \
        TEST(type, f, MUL(l), (r = MUL(l)(-57, -21)) == 1197); \
    }

#define DIV(l) __div##l##i3
#define UDIV(l) __udiv##l##i3

#define DIV_TESTS(l, f, type) \
    { \
        TEST(type, f, DIV(l), !(r = DIV(l)(3, 4))); \
        TEST(type, f, DIV(l), (r = DIV(l)(489, 45)) == 10); \
        TEST(type, f, DIV(l), (r = DIV(l)(489, -56)) == -8); \
        TEST(type, f, DIV(l), (r = DIV(l)(-265, 8)) == -33); \
        TEST(type, f, DIV(l), (r = DIV(l)(-464, -15)) == 30); \
        /* NOTE: The test below is very likely to always pass on CPUs having no
         * hardware instruction for division. */ \
        TEST(type, f, DIV(l), (r = DIV(l)(type##_max, 7)) == type##_max/7); \
    }

#define UDIV_TESTS(l, f, type) \
    { \
        TEST(type, f, UDIV(l), !(r = UDIV(l)(56, 234))); \
        TEST(type, f, UDIV(l), (r = UDIV(l)(568, 25)) == 22); \
        /* NOTE: The test below is very likely to always pass on CPUs having no
         * hardware instruction for division. */ \
        TEST(type, f, UDIV(l), \
             (r = UDIV(l)(u##type##_max, 3)) == u##type##_max/3); \
    }

#define MOD(l) __mod##l##i3
#define UMOD(l) __umod##l##i3

#define MOD_TESTS(l, f, type) \
    { \
        TEST(type, f, MOD(l), (r = MOD(l)(23, 3)) == 2); \
        TEST(type, f, MOD(l), (r = MOD(l)(-56, 5)) == -1); \
        TEST(type, f, MOD(l), (r = MOD(l)(65, -9)) == 2); \
        TEST(type, f, MOD(l), (r = MOD(l)(-89, -23)) == -20); \
        TEST(type, f, MOD(l), !(r = MOD(l)(225, 25))); \
    }

#define UMOD_TESTS(l, f, type) \
    { \
        TEST(type, f, UMOD(l), (r = UMOD(l)(23, 3)) == 2); \
        TEST(type, f, UMOD(l), !(r = UMOD(l)(225, 25))); \
    }

#define NEG(l) __neg##l##i2

#define NEG_TESTS(l, f, type) \
    { \
        TEST(type, f, NEG(l), (r = NEG(l)(-6)) == 6); \
        TEST(type, f, NEG(l), (r = NEG(l)(189)) == -189); \
    }

#if URT_NONANSI
#define _LONGLONG_TESTS(str, macro) \
    { \
        puts("+- " str " tests for long longs..."); \
        macro(t, "%lld", longlong); \
    }
#else
#define _LONGLONG_TESTS(str, macro)
#endif

#define TESTL(str, macro) \
    { \
        puts("+- " str " tests for longs..."); \
        macro(d, "%ld", long); \
        _LONGLONG_TESTS(str, macro); \
    }

#define TESTI(str, macro) \
    { \
        puts("+- " str " tests for ints..."); \
        macro(s, "%d", int); \
        TESTL(str, macro); \
    }

#if URT_NONANSI
typedef long long longlong;
#endif

int main(int argc, char **argv) {
    int opt;
    const int int_bits = sizeof(int)*CHAR_BIT;
    const int int_max = INT_MAX;
    const unsigned int uint_max = UINT_MAX;
    const int long_bits = sizeof(long)*CHAR_BIT;
    const long long_max = LONG_MAX;
    const unsigned long ulong_max = ULONG_MAX;
#if URT_NONANSI
    const int longlong_bits = sizeof(long long)*CHAR_BIT;
    const long long longlong_max = LLONG_MAX;
    const unsigned long long ulonglong_max = ULLONG_MAX;
#endif

    while((opt = getopt(argc, argv, "h")) != -1){
        switch(opt){
            case 'h':
                fprintf(stderr, help_str, argv[0]);
                return EXIT_SUCCESS;
        }
    }

    TESTI("Shift", SHIFT_TESTS);
    TESTI("Multiplication", MUL_TESTS);
    TESTI("Signed division", DIV_TESTS);
    TESTI("Unsigned division", UDIV_TESTS);
    TESTI("Signed modulo", MOD_TESTS);
    TESTI("Unsigned modulo", UMOD_TESTS);
    TESTL("Sign changing subroutines", NEG_TESTS);

    puts("+- All tests passed successfully!");

    return EXIT_SUCCESS;
}
