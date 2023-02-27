#include <chrono>
#include <stdlib.h>
#include <iostream>
#include <omp.h>
#define SIZE (1024*1024*128)
#define ITERS (16)

int main(int argc, char ** argv) {
  int *a, *b, *c;
  a = (int *) malloc(sizeof(int)*SIZE);
  b = (int *) malloc(sizeof(int)*SIZE);
  c = (int *) malloc(sizeof(int)*SIZE);

  for (int i = 0; i < SIZE; i++) {
    c[i] = b[i] = a[i] = 0;
  }

  int num_threads = 8;
  if (argc > 1) {
    num_threads = atoi(argv[1]);
  }
  std::cout << "num threads " << num_threads << std::endl;

  omp_set_num_threads(num_threads);


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
