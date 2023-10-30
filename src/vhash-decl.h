#ifndef V_HASH_H
#define V_HASH_H
#include <stdint.h>

#if __cplusplus
extern "C" {
#endif

/* Copyright 2023 Melissa O'Neill, Wang Yi, Austin Appleby, & Richard Van Natta
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to * permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * This is a vendored blend of a few permissive hashing and rng libraries:
 *
 *    PCG Random by Melissa O'Neill http://www.pcg-random.org/ (MIT)
 *    Wyhash by Wang Yi https://github.com/wangyi-fudan/wyhash (Public Domain)
 *    Murmur3 by Austin Appleby https://github.com/aappleby/smhasher (Public Domain)
 * 
 * There are very few changes to the base libraries and it's a thin wrapper over
 * them. As a consequence, this derivative cocktail is licensed under MIT.
 */

/** Non-cryptographic hash. Seed can be any value including zero. Uses
 *  wyhash with default salting. Note that it does unaligned reads and
 *  uses 128 bit multiplication.
 */
static inline uint64_t vhash(const void *dat, size_t len, uint64_t seed);
/** Non-cryptographic small-value hash. Seed can be any value including zero. Can
 *  be used to fold together hashes ie in hashing a linked list. Uses wyhash64 with
 *  default salting.
 */
static inline uint64_t vhash64(uint64_t x, uint64_t seed);
/** Non-cryptographic and invertible bit mixer. Can be used to quickly hash small
 *  values. Uses a variant of the murmur3 finalizer.
 */
static inline uint64_t vhash64_quick(uint64_t x);

typedef struct vrandom_state vrandom_state;
/** Initialize an rng state. Seed and streamid can be any value. The top bit of streamid
 *  is ignored. Streamid is used to provide multiple rngs from the
 *  same seed, ie for multithreading.
 */
static inline void vsrandom(vrandom_state * state, uint64_t seed, uint64_t streamid);
/** Returns a random uniform integer in the range from 0 to UINT32_MAX, inclusively, and
 *  advances the rng state once. Uses the excellent pcg-random32 function. Thread unsafe.
 */
static inline uint32_t vrandom(vrandom_state * state);
/** Returns a random uniform integer in the range from 0 to bounds-1, inclusively, and advances
 *  the rng state once. Uses the excellent pcg-random32 function. Very thread unsafe.
 */
static inline uint32_t vrandom_bounded(vrandom_state * state, uint64_t bounds);
/** Returns a random uniform double in the range from 0 to 1, inclusively, and advances the
 *  rng state once. Uses the excellent pcg-random32 function. Granularity is currently 2^-32. 
 */
static inline double vrandom_double(vrandom_state * state);
/** Efficiently advances the rng state n steps in log(n) time. To go backwards, pass a signed
 *  int and let the rng state wraparound.
 */
static inline void vrandom_advance(vrandom_state * state, uint64_t n);

#if __cplusplus
}
#endif

#endif
