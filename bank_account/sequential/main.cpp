#include <iostream>
using namespace std;

#define HOURS 1024*1024

int tylers_account = 0;

void ucsc_pays_tyler() {
  tylers_account += 1;
}

void tyler_buys_coffee() {
  tylers_account -= 1;
}

int main() {

  for (int i = 0; i < HOURS; i++) {
    ucsc_pays_tyler();
    tyler_buys_coffee();
  }

  cout << "tyler's account balance: " << tylers_account << endl;
  return 0;
}
