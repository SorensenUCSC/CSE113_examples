#pragma once

#include <atomic>
using namespace std;

class mutex {
 public:
  mutex() {
    flag = 0;
  }
    
  void lock() {
    bool e = false;
    bool acquired = false;
    while (!acquired) {
      while (flag.load(memory_order_relaxed) == true);
      e = false;
      acquired = atomic_compare_exchange_strong(&flag, &e, true);
    }
  }
  
  void unlock() {
    flag.store(false);
  }

 private:
  atomic_bool flag;
};
