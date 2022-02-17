#include <thread>
#include <iostream>
#include <atomic>
#include "bank_account.h"
using namespace std;

#define HOURS 1024 * 1024

atomic<bank_account> tylers_account;

void buy_many_coffees() {
  for (int i = 0; i < HOURS; i++) {
    bank_account local = tylers_account.load();
    local.buy_coffee();
    tylers_account.store(local);
  }
}

void work_at_ucsc() {
  for (int i = 0; i < HOURS; i++) {
    bank_account local = tylers_account.load();
    local.work_one_hour();
    tylers_account.store(local);
  }
}

int main() {
  thread coffee = thread(buy_many_coffees);
  thread work = thread(work_at_ucsc);

  coffee.join();
  work.join();

  cout << "balance: " << tylers_account.load().get_balance() << endl;;
  return 0;

  
}
