// #####################################################################
//  Copyright (c) 2010-2011, Eftychios Sifakis.
//
//  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
//  following conditions are met:
//    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
//    disclaimer.
//    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
//    following disclaimer in the documentation and/or
//      other materials provided with the distribution.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
//  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// #####################################################################

#ifdef PRINT_DEBUGGING_OUTPUT
#include <iomanip>
#include <iostream>
#endif

#ifdef USE_SCALAR_IMPLEMENTATION
#define ENABLE_SCALAR_IMPLEMENTATION(X) X
#else
#define ENABLE_SCALAR_IMPLEMENTATION(X)
#endif

#ifdef USE_SSE_IMPLEMENTATION
#include <xmmintrin.h>
#define ENABLE_SSE_IMPLEMENTATION(X) X
#else
#define ENABLE_SSE_IMPLEMENTATION(X)
#endif

#ifdef USE_AVX_IMPLEMENTATION
#include <immintrin.h>
#define ENABLE_AVX_IMPLEMENTATION(X) X
#else
#define ENABLE_AVX_IMPLEMENTATION(X)
#endif

#ifdef USE_NEON_IMPLEMENTATION
#include <arm_neon.h>
#define ENABLE_NEON_IMPLEMENTATION(X) X
#else
#define ENABLE_NEON_IMPLEMENTATION(X)
#endif

#ifdef USE_SCALAR_IMPLEMENTATION

float rsqrt(float x) {
    // int ihalf = *(int *)&x - 0x00800000; // Alternative to next line,
    // float xhalf = *(float *)&ihalf;      // for sufficiently large nos.
    float xhalf = 0.5f * x;
    int i = *(int *)&x;             // View x as an int.
                                    // i = 0x5f3759df - (i >> 1);   // Initial guess (traditional).
    i = 0x5f375a82 - (i >> 1);      // Initial guess (slightly better).
    x = *(float *)&i;               // View i as float.
    x = x * (1.5f - xhalf * x * x); // Newton step.
                                    // x = x*(1.5008908 - xhalf*x*x);  // Newton step for a balanced error.
    return x;
}

#endif
