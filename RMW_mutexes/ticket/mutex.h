#pragma once

#include <atomic>
using namespace std;

class mutex {
 public:
  mutex() {
    now_serving = 0;
    counter = 0;
  }
    
  void lock(int thread_id) {
    int my_num = atomic_fetch_add(&counter,1);
    while(my_num != now_serving.load());

  }
  
  void unlock(int thread_id) {
    int tmp = now_serving.load();
    tmp += 1;
    now_serving.store(tmp);
  }

 private:
  atomic_int counter;
  atomic_int now_serving;
};
