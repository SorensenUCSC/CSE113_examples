#include <iostream>
#include <thread>
using namespace std;

#define ITERS (1024*1024)

#define FENCE asm volatile ("mfence" : : : "memory")

volatile int x = 0;
volatile int y = 0;
int r0 = 0;
int r1 = 0;

void thread0() {
  x = 1;
  FENCE;
  r0 = y;
}

void thread1() {
  y = 1;
  FENCE;
  r0 = x;
}


int main() {
  for (int i = 0; i < ITERS; i++) {
    thread t0 = thread(thread0);
    thread t1 = thread(thread1);
    t0.join();
    t1.join();

    if (r0 == 0 && r1 == 0) {
      cout << "saw weird behavior" << endl;
    }

    x = y = r0 = r1 = 0;
  }
    
  
    
}
