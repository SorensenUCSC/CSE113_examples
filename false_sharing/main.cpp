#include "stdlib.h"

#define NUM_ELEMENTS 8
#define ITERATIONS 1024 * 1024 * 256

void repeat_increment(volatile int *a) {
  for (int i = 0; i < ITERATIONS; i++) {
    int tmp = *a;
    tmp += 1;
    *a = tmp;
  }
}

int main() {
  int ar[NUM_ELEMENTS];

  for (int i = 0; i < NUM_ELEMENTS; i++) {
    ar[i] = 0;
  }

  
  for (int i = 0; i < NUM_ELEMENTS; i++) {
    repeat_increment(ar+i);
  }
}
