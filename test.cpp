#include <assert.h>
#include <stdio.h>
#include "vhash.h"

int main() {
  uint64_t seed = 0xDEADBEEF;
  // Fast General purpose non-cryptographic hash
  uint64_t hash1 = vhash("hello, world!", sizeof "hello, world!", seed);
  printf("%016llx\n", hash1);

  // Faster small value non-cryptographic hash, use for objects <= 8 bytes
  // Also use to glue two hashes together, eg in hashing linked lists
  uint64_t hash2 = vhash64(12345, seed);
  printf("%016llx\n", hash2);

  // Fastest small value non-cryptographic hash, but invertible & no seeding
  uint64_t hash3 = vhash64_quick(12345);
  printf("%016llx\n", hash3);

  int threadid = 0;
  vrandom_state rng;

  // Setup rng state. the 3rd parameter provides multiple streams per
  // seed, eg for multithreading.
  vsrandom(&rng, seed, threadid);

  // Get a uniform integer from 0 to 2^32-1
  uint32_t randint = vrandom(&rng);
  printf("%08x\n", randint);

  // Get a uniform integer from 1 to 20
  int d20 = vrandom_bounded(&rng, 20) + 1;
  printf("%d\n", d20);

  // Get a uniform double from 0 to 1
  double U0 = vrandom_double(&rng);
  printf("%f\n", U0);

  // Rewind the rng 1 step and get the same result
  vrandom_advance(&rng, -1);
  double U1 = vrandom_double(&rng);
  printf("%f\n", U1);
  assert(U0 == U1);

}
