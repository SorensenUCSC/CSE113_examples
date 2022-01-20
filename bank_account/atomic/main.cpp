#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

#define HOURS 1024 * 1024

atomic_int tylers_account(0);

void ucsc_pays_tyler() {
  atomic_fetch_add(&tylers_account,1);
}

void tyler_buys_coffee() {
  for (int i = 0; i < HOURS; i++) {
    atomic_fetch_add(&tylers_account,-1);
  }
}

int main() {

  thread t = thread(tyler_buys_coffee);

  for (int i = 0; i < HOURS; i++) {
    ucsc_pays_tyler();
  }
  t.join();
  cout << "tyler's account balance: " << tylers_account << endl;

  return 0;
}
