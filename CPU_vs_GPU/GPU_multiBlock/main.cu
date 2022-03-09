#include <thread>
#include <assert.h>
#include <chrono>
#include <iostream>
using namespace std::chrono;
using namespace std;

#define SIZE (1024*1024)
#define OUTER (1024)

__global__ void vector_add(double * d_a, double * d_b, double * d_c, int size) {
  int global_id = (blockIdx.x * blockDim.x) + threadIdx.x;
  int i = global_id;
  for (int j = 0; j < OUTER; j++) {
    d_a[i] = d_b[i] + d_c[i];
  }
}


int main() {

  double *a = new double[SIZE];
  double *b = new double[SIZE];
  double *c = new double[SIZE];

  for(int i = 0; i < SIZE; i++) {
    a[i] = 0;
    b[i] = i;
    c[i] = 1;
  }

  double *d_a, *d_b, *d_c;
  int e = 0;
  e = cudaMalloc(&d_a, SIZE*sizeof(double));
  e |= cudaMalloc(&d_b, SIZE*sizeof(double));
  e |= cudaMalloc(&d_c, SIZE*sizeof(double));




  e |= cudaMemcpy(d_a, a, SIZE*sizeof(double), cudaMemcpyHostToDevice);
  e |= cudaMemcpy(d_b, b, SIZE*sizeof(double), cudaMemcpyHostToDevice);
  e |= cudaMemcpy(d_c, c, SIZE*sizeof(double), cudaMemcpyHostToDevice);



  auto time_start = high_resolution_clock::now();
  vector_add<<<1024,1024>>>(d_a, d_b, d_c, SIZE);
  e |= cudaDeviceSynchronize();

  auto time_end = high_resolution_clock::now();
  auto time_duration = duration_cast<nanoseconds>(time_end - time_start);
  double time_seconds = time_duration.count()/1000000000.0;
  
  cout << "timings: " << time_seconds << endl;

  cudaMemcpy(a, d_a, SIZE*sizeof(double), cudaMemcpyDeviceToHost); 
      
  for (int i = 0; i < SIZE; i++) {
    assert(a[i] == (i + 1));    
  }  

  return 0;
}


  
