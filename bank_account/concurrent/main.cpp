#include <iostream>
#include <thread>
using namespace std;

#define HOURS 1024 * 1024

volatile int tylers_account = 0;

void ucsc_pays_tyler() {
  for (int i = 0; i < HOURS; i++) {
    tylers_account += 1;
  }
}

void tyler_buys_coffee() {
  for (int i = 0; i < HOURS; i++) {
    tylers_account -= 1;
  }
}

int main() {

  thread t0 = thread(tyler_buys_coffee);
  thread t1 = thread(ucsc_pays_tyler);
  t0.join();
  t1.join();

  cout << "tyler's account balance: " << tylers_account << endl;

  return 0;
}
