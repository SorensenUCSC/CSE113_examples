#include <thread>
#include <assert.h>
#include <chrono>
#include <iostream>
using namespace std::chrono;
using namespace std;

#define SIZE (1024*1024*32)
#define OUTER (128)

void vec_add(double *a, double *b, double *c, int size, int tid, int num_threads) {
  int chunk = size / num_threads;
  int start = chunk * tid;
  int end = start + chunk;
  for (int j = 0; j < OUTER; j++) {
    for (int i = start; i < end; i++) {
      a[i] = b[i] + c[i];
    }
  }
}

int main(int argc, char *argv[]) {
  int num_threads = 4;
  if (argc > 1) {
    num_threads = atoi(argv[1]);
  }

  double *a = new double[SIZE];
  double *b = new double[SIZE];
  double *c = new double[SIZE];

  for(int i = 0; i < SIZE; i++) {
    a[i] = 0;
    b[i] = i;
    c[i] = 1;
  }

  thread thread_array[num_threads];

  auto time_start = high_resolution_clock::now();

  for (int i = 0; i < num_threads; i++) {
    thread_array[i] = thread(vec_add,a,b,c,SIZE,i,num_threads);
  }
  
  for (int i = 0; i < num_threads; i++) {
    thread_array[i].join();
  }
  
  auto time_end = high_resolution_clock::now();
  auto time_duration = duration_cast<nanoseconds>(time_end - time_start);
  double time_seconds = time_duration.count()/1000000000.0;
  
  cout << "timings: " << time_seconds << endl;
    
  for (int i = 0; i < SIZE; i++) {
    assert(a[i] == (i + 1));
  }  
}
