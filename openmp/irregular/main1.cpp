#include <thread>
#include "util.h"
#include <chrono>
#include <iostream>
#include <omp.h>
#include "checker.h"

ScheduleType t = static_t;


int main(int argc, char **argv) {
  float* result_parallel = new float[SIZE];
  int* mult = new int[SIZE];
  for (int i = 0; i < SIZE; i++) {
    result_parallel[i] = i;
  }
  linear_work(mult, SIZE);

  int num_threads = 4;
  if (argc > 1) {
    num_threads = atoi(argv[1]);
  }
  std::cout << "num threads " << num_threads << std::endl;

  omp_set_num_threads(num_threads);


  // Launch NUM_THREADS threads and then join them

  auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel for schedule(dynamic)
  for (int i = 0; i < SIZE; i++) {
    float base = result_parallel[i];
    for (int w = 0; w < mult[i]-1; w++) {
      result_parallel[i] = result_parallel[i]+base;
    }
  }


  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  double seconds = duration.count()/1000000000.0;
  check_results(result_parallel, SIZE, t);
  check_timing(seconds, t);

  std::cout << "time (seconds): " << seconds << std::endl;

  return 0;
}
