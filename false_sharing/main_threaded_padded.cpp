#include "stdlib.h"
#include <thread>
using namespace std;

#define NUM_ELEMENTS 8
#define ITERATIONS 1024 * 1024 * 256
#define CACHE_LINE_INT 16

void repeat_increment(volatile int *a) {
  for (int i = 0; i < ITERATIONS; i++) {
    int tmp = *a;
    tmp += 1;
    *a = tmp;
  }
}

int main() {
  int ar[NUM_ELEMENTS*CACHE_LINE_INT];
  thread thread_ar[NUM_ELEMENTS];

  for (int i = 0; i < NUM_ELEMENTS; i++) {
    ar[i*CACHE_LINE_INT] = 0;
  }
 
  for (int i = 0; i < NUM_ELEMENTS; i++) {
    thread_ar[i] = thread(repeat_increment, ar+(i*CACHE_LINE_INT));
  }

  for (int i = 0; i < NUM_ELEMENTS; i++) {
    thread_ar[i].join();
  }
}
