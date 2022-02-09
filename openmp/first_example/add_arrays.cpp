#include <chrono>
#include <stdlib.h>
#include <iostream>
#define SIZE (1024*1024*128)
#define ITERS (16)

int main() {
  int *a, *b, *c;
  a = (int *) malloc(sizeof(int)*SIZE);
  b = (int *) malloc(sizeof(int)*SIZE);
  c = (int *) malloc(sizeof(int)*SIZE);

  for (int i = 0; i < SIZE; i++) {
    c[i] = b[i] = a[i] = 0;
  }


  auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel for 
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < ITERS; j++) {
      c[i] = a[i] + b[i];
    }
  }

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);


  double seconds = duration.count()/1000000000.0;
  std::cout << "time (seconds): " << seconds << std::endl;
}
