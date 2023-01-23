#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

#define HOURS 1024 * 1024
//#define OVERHEAD this_thread::sleep_for (chrono::milliseconds(1));

int tylers_account = 0;
mutex tylers_account_mutex;

void ucsc_pays_tyler() {
  for (int i = 0; i < HOURS; i++) {
    tylers_account_mutex.lock();
    tylers_account += 1;
    tylers_account_mutex.unlock();
  }
}

// What happens if we move the mutex outside the 'for' loop?
void tyler_buys_coffee() {
  for (int i = 0; i < HOURS; i++) {
    tylers_account_mutex.lock();
    tylers_account -= 1;
    if (tylers_account < -20000) {
      printf("Warning!\n");
      return;
    }
    tylers_account_mutex.unlock();
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
