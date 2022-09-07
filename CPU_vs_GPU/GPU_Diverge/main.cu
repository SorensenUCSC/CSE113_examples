#include <thread>
#include <assert.h>
#include <chrono>
#include <iostream>
using namespace std::chrono;
using namespace std;

#define SIZE (1024*1024*32)
#define OUTER (128)

__global__ void vector_add(float * d_a, float * d_b, float * d_c, int size) {
  int global_id = (blockIdx.x * blockDim.x) + threadIdx.x;
  if (global_id % 4 == 0) {
    for (int j = 0; j < OUTER; j++) {
      d_a[global_id] = d_b[global_id] + d_c[global_id];
    }
  }
  else if (global_id % 4 == 1) {
    for (int j = 0; j < OUTER; j++) {
      d_a[global_id] = d_b[global_id] * d_c[global_id];
    }    
  }
  else if (global_id % 4 == 2) {
    for (int j = 0; j < OUTER; j++) {
      d_a[global_id] = d_b[global_id] / d_c[global_id];
    }
  }
  else if (global_id % 4 == 3) {
    for (int j = 0; j < OUTER; j++) {
      d_a[global_id] = d_b[global_id] - d_c[global_id];
    }    
  }
}

__global__ void vector_add_chunked(float * d_a, float * d_b, float * d_c, int size) {
  int global_id = (blockIdx.x * blockDim.x) + threadIdx.x;
  if (global_id < (size/4)*1) {
    for (int j = 0; j < OUTER; j++) {
      d_a[global_id] = d_b[global_id] + d_c[global_id];
    }
  }
  else if (global_id < (size/4)*2) {
    for (int j = 0; j < OUTER; j++) {
      d_a[global_id] = d_b[global_id] * d_c[global_id];
    }    
  }
  else if (global_id < (size/4)*3) {
    for (int j = 0; j < OUTER; j++) {
      d_a[global_id] = d_b[global_id] / d_c[global_id];
    }
  }
  else if (global_id < (size/4)*4) {
    for (int j = 0; j < OUTER; j++) {
      d_a[global_id] = d_b[global_id] - d_c[global_id];
    }    
  }
}



int main() {

  float *a = new float[SIZE];
  float *b = new float[SIZE];
  float *c = new float[SIZE];

  for(int i = 0; i < SIZE; i++) {
    a[i] = 0.0f;
    b[i] = i;
    c[i] = 1.0f;
  }

  float *d_a, *d_b, *d_c;
  int e = 0;
  e = cudaMalloc(&d_a, SIZE*sizeof(float));
  e |= cudaMalloc(&d_b, SIZE*sizeof(float));
  e |= cudaMalloc(&d_c, SIZE*sizeof(float));




  e |= cudaMemcpy(d_a, a, SIZE*sizeof(float), cudaMemcpyHostToDevice);
  e |= cudaMemcpy(d_b, b, SIZE*sizeof(float), cudaMemcpyHostToDevice);
  e |= cudaMemcpy(d_c, c, SIZE*sizeof(float), cudaMemcpyHostToDevice);



  auto time_start = high_resolution_clock::now();
  vector_add<<<1024*32,1024>>>(d_a, d_b, d_c, SIZE);
  e |= cudaDeviceSynchronize();

  auto time_end = high_resolution_clock::now();
  auto time_duration = duration_cast<nanoseconds>(time_end - time_start);
  double time_seconds = time_duration.count()/1000000000.0;
  
  cout << "timings: " << time_seconds << endl;

  e |= cudaMemcpy(a, d_a, SIZE*sizeof(float), cudaMemcpyDeviceToHost); 
      
  for (int i = 0; i < SIZE; i++) {
    assert(a[i] == (float(i) + 1.0f));    
  }  

  return 0;
}
