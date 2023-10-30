#include <stdio.h>
#include <math.h>
#include "vhash.h"

int main() {
  printf("%lX\n", vhash64(0, 1));
  printf("%lX\n", vhash64(1, 0));

  vrandom_state rng;
  vsrandom(&rng, 0, 0);

  int buckets[32] = { 0 };
  for(int i = 0; i < 1000000; i++) {
    double d = vrandom_double(&rng);
    if(d >= 1.0) d = 0.99999;
    int roll = floor(d * 32);
    buckets[roll]++;
  }
  for(int i = 0; i < 32; i++) {
    printf("%d\n", buckets[i]);
  }

  printf("%f\n", vrandom_double(&rng));
  vrandom_advance(&rng, -1);
  printf("%f\n", vrandom_double(&rng));
  printf("%f\n", vrandom_double(&rng));

}
