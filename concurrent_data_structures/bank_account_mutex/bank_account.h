#include <mutex>
using namespace std;

class bank_account {
 public:
  bank_account() {
    balance = 0;
  }

  void buy_coffee() {
    m.lock();
    balance -= 1;
    m.unlock();
  }

  void work_one_hour() {
    m.lock();
    balance += 1;
    m.unlock();
  }

  int get_balance() {
    return balance;
  }


 private:
  mutex m;
  int balance;
};
