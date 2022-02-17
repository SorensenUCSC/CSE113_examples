class bank_account {
 public:
  bank_account() {
    balance = 0;
  }

  void buy_coffee() {
    balance -= 1;
  }

  void work_one_hour() {
    balance += 1;
  }

  int get_balance() {
    return balance;
  }


 private:
  int balance;
};
