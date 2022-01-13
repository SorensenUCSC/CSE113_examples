#include <thread>
using namespace std;

// This function will be executed by many different threads
void increment_array(int *a, int a_size, int tid, int num_threads) { 
   for (int i = tid; i < a_size; i+=num_threads) { 
       a[i]++; 
   } 
}

#define THREADS 8 
#define A_SIZE 1024 
int main() { 
  int *a = new int[A_SIZE];

  // initialize a
  for (int i = 0; i < A_SIZE; i++) {
    a[i] = 0;
  }

  // Create a pointer to an array of threads
  thread thread_ar[THREADS];

  // launch the threads
  for (int i = 0; i < THREADS; i++) { 
    thread_ar[i] = thread(increment_array, a, A_SIZE, i, THREADS); 
  }

  // join the threads
  for (int i = 0; i < THREADS; i++) { 
    thread_ar[i].join(); 
  }

  // free the memory
  delete[] a;
  
  return 0; 
}

