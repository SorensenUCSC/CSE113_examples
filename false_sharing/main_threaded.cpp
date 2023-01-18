#include "stdlib.h"
#include <chrono>
#include <iostream>
#include <thread>
using namespace std;
using namespace std::chrono;

#include "common.h"

void repeat_increment(volatile int *a) {
  for (int i = 0; i < ITERATIONS; i++) {
    int tmp = *a;
    tmp += 1;
    *a = tmp;
  }
}

int main() {
  int ar[NUM_ELEMENTS];
  thread thread_ar[NUM_ELEMENTS];

  for (int i = 0; i < NUM_ELEMENTS; i++) {
    ar[i] = 0;
  }

  auto start = high_resolution_clock::now();
  for (int i = 0; i < NUM_ELEMENTS; i++) {
    thread_ar[i] = thread(repeat_increment, ar+i);
  }

  for (int i = 0; i < NUM_ELEMENTS; i++) {
    thread_ar[i].join();
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<nanoseconds>(stop - start);
  double seconds = duration.count()/1000000000.0;
  
  cout << seconds << " s\n";

}
