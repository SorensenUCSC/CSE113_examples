#include <thread>
#include <iostream>
#include "bank_account.h"
using namespace std;

#define HOURS (1024 * 1024)

bank_account tylers_account;

void buy_many_coffees() {
  for (int i = 0; i < HOURS; i++) {
    tylers_account.buy_coffee();
  }
}

void work_at_ucsc() {
  for (int i = 0; i < HOURS; i++) {
    tylers_account.work_one_hour();
  }
}

int main() {
  thread coffee = thread(buy_many_coffees);
  thread work = thread(work_at_ucsc);

  coffee.join();
  work.join();

  cout << "balance: " << tylers_account.get_balance() << endl;;
  return 0;

  
}
