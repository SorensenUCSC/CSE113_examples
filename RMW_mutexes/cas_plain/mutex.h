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
    int acquired = false;
    while (acquired == false) {
      acquired = atomic_compare_exchange_strong(&flag, &e, true);
      e = false;	
    }
  }

  bool try_lock() {
    bool e = false;
    return atomic_compare_exchange_strong(&flag, &e, true);
  }
  
  void unlock() {
    flag.store(false);
  }

 private:
  atomic_bool flag;
};
