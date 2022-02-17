class bank_account {
 public:
  bank_account() {
    balance = 0;
    time = 0.0;
    location = 0;
    rewards = 0;
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

  // extra info
  double time;
  int location;
  int rewards;
};
