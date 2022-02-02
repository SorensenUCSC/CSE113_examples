#include <mutex>
#include <atomic>
using namespace std;

class bank_account {
 public:
  bank_account() {
    balance = 0;
  }

  void buy_coffee() {
    atomic_fetch_add(&balance, -1);
  }

  void work_one_hour() {
    atomic_fetch_add(&balance, 1);
  }

  int get_balance() {
    return balance;
  }


 private: 
  atomic_int balance;
};
