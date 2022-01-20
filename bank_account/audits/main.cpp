#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

#define HOURS 1024*1024
#define AUDIT(x,y)
#define NUM_AUDITS 1024
#define OVERHEAD this_thread::sleep_for (chrono::milliseconds(1));

int tylers_personal_account = 0;
int tylers_business_account = 0;
mutex tylers_personal_account_mutex;
mutex tylers_business_account_mutex;

void ucsc_pays_tyler_personal() {
  tylers_personal_account_mutex.lock();
  tylers_personal_account += 1;
  tylers_personal_account_mutex.unlock();
}

void ucsc_pays_tyler_business() {
  tylers_business_account_mutex.lock();
  tylers_business_account += 1;
  tylers_business_account_mutex.unlock();
}

void tyler_buys_coffee_personal() {
  tylers_personal_account_mutex.lock();
  tylers_personal_account -= 1;
  tylers_personal_account_mutex.unlock();
}

void tyler_buys_coffee_business() {
  tylers_business_account_mutex.lock();
  tylers_business_account -= 1;
  tylers_business_account_mutex.unlock();
}

void tyler_buys_coffee() {
  for (int i = 0; i < HOURS; i++) {
    tyler_buys_coffee_personal();
    tyler_buys_coffee_business();
  }
}

void ucsc_audit() {
  for (int i = 0; i < NUM_AUDITS; i++) {
    tylers_personal_account_mutex.lock();
    tylers_business_account_mutex.lock();

    AUDIT(tylers_personal_account, tylers_business_account);
    
    tylers_business_account_mutex.unlock();
    tylers_personal_account_mutex.unlock();
  }
}

void irs_audit() {
  for (int i = 0; i < NUM_AUDITS; i++) {
    tylers_personal_account_mutex.lock();
    tylers_business_account_mutex.lock();
    
    AUDIT(tylers_personal_account, tylers_business_account);
    
    tylers_personal_account_mutex.unlock();
    tylers_business_account_mutex.unlock();
  }
}


int main() {

  thread t = thread(tyler_buys_coffee);
  thread ucsc = thread(ucsc_audit);
  thread irs = thread(irs_audit);

  for (int i = 0; i < HOURS; i++) {
    ucsc_pays_tyler_personal();
    ucsc_pays_tyler_business();
  }
  t.join();
  ucsc.join();
  irs.join();

  cout << "tyler's personal account balance: " << tylers_personal_account << endl;
  cout << "tyler's business account balance: " << tylers_business_account << endl;

  return 0;
}
