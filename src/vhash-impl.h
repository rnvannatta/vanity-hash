#ifndef V_HASH_IMPL_H
#define V_HASH_IMPL_H 1
#include <stdint.h>

#if __cplusplus
extern "C" {
#endif

static inline uint64_t vhash(const void *dat, size_t len, uint64_t seed) {
  return wyhash(dat, len, seed, _wyp);
}

static inline uint64_t vhash64(uint64_t x, uint64_t seed) {
  return wyhash64(x, seed);
}

static inline uint64_t vhash64_quick(uint64_t x) {
  // Murmur3 based mixer optimized for low entropy keys
  // Mix 13 from https://zimbry.blogspot.com/2011/09/better-bit-mixing-improving-on.html
  // This is actually considerably better than the base murmurhash
  // Note that this function is invertible.
  uint64_t magic1 = 0xbf58476d1ce4e5b9ull;
  uint64_t magic2 = 0x94d049bb133111ebull;

  uint64_t shift1 = 30;
  uint64_t shift2 = 27;
  uint64_t shift3 = 31;

  x ^= (x >> shift1);
  x *= magic1;
  x ^= (x >> shift2);
  x *= magic2;
  x ^= (x >> shift3);

  return x;
}

struct vrandom_state {
  pcg32_random_t state;
};

static inline void vsrandom(vrandom_state * state, uint64_t seed, uint64_t streamid) {
  return pcg32_srandom_r(&state->state, seed, streamid);
}
static inline uint32_t vrandom(vrandom_state * state) {
  return pcg32_random_r(&state->state);
}
static inline uint32_t vrandom_bounded(vrandom_state * state, uint64_t bounds) {
  return pcg32_boundedrand_r(&state->state, bounds); 
}

static inline double vrandom_double(vrandom_state * state) {
  return (double)vrandom(state) * 0x1.0p-32;
}

static inline void vrandom_advance(vrandom_state * state, uint64_t n) {
  pcg32_advance_r(&state->state, n);
}

#if __cplusplus
}
#endif

#endif
