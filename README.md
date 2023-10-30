# PRNG and Hashes for Vanity Scheme

This is just a vendored collection of excellent hashing and prng functions, glued into a single header file with a thin wrapper over the originals. These are used in [Vanity Scheme](https://github.com/rnvannatta/vanity-scheme/)

* [PCG32 Random](https://www.pcg-random.org/)
* [Wyhash](https://github.com/wangyi-fudan/wyhash)
* [Murmur3's Mixer](https://github.com/aappleby/smhasher)

This collection is currently licensed under MIT.

## Install Instructions

Copy `include/vhash.h` into your project. It is compatible with C99 and C++17. Good performance requires 128 bit multiplication support. The hashing function does unaligned reads, though it should be endianness safe.

## Usage

```C
uint64_t seed = 0xDEADBEEF;
// Fast General purpose non-cryptographic hash
uint64_t hash1 = vhash("hello, world!", sizeof "hello, world!", seed);

// Faster small value non-cryptographic hash, use for objects <= 8 bytes
// Also use to glue two hashes together, eg in hashing linked lists
uint64_t hash2 = vhash64(12345, seed);

// Fastest small value non-cryptographic hash, but invertible & no seeding
uint64_t hash3 = vhash64_quick(12345);

int threadid = 0;
vrandom_state rng;

// Setup rng state. the 3rd parameter provides multiple streams per
// seed, eg for multithreading.
vsrandom(&rng, seed, threadid);

// Get a uniform integer from 0 to 2^32-1
uint32_t randint = vrandom(&rng);

// Get a uniform integer from 1 to 20
int d20 = vrandom_bounded(&rng, 20) + 1;

// Get a uniform double from 0 to 1
double U0 = vrandom_double(&rng);

// Rewind the rng 1 step and get the same result
vrandom_advance(&rng, -1);
double U1 = vrandom_double(&rng);
assert(U0 == U1);
```
