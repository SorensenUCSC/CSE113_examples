#include <thread>
#include <iostream>
#include <atomic>
#include "bank_account.h"
using namespace std;

#define HOURS 1024*1024

atomic<bank_account> tylers_account;

void buy_many_coffees() {
  bank_account snapshot;
  bank_account update;
  bool success;
  for (int i = 0; i < HOURS; i++) {
    do {
    bank_account snapshot = tylers_account.load();
    bank_account update = snapshot;
    update.buy_coffee();
    success = tylers_account.compare_exchange_strong(snapshot, update);
    } while (success == false);
  }
}

void work_at_ucsc() {
  bank_account snapshot;
  bank_account update;
  bool success;
  for (int i = 0; i < HOURS; i++) {
    do {
    bank_account snapshot = tylers_account.load();
    bank_account update = snapshot;
    update.work_one_hour();
    success = tylers_account.compare_exchange_strong(snapshot, update);
    } while (success == false);
  }
}

int main() {
  thread coffee = thread(buy_many_coffees);
  thread work = thread(work_at_ucsc);

  coffee.join();
  work.join();

  cout << "is atomic int lock free? " << tylers_account.is_lock_free() << endl;
  cout << "balance: " << tylers_account.load().get_balance() << endl;;
  return 0;  
}
