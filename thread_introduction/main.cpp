#include <thread>
#include <iostream>
#include <chrono>
using namespace std; 

void foo(int a, int b, int &c) {
  c = a + b;
} 

int main() { 
  // some main code
  int c = 0;
  thread thread_handle (foo,1,2,ref(c));

  //  std::this_thread::sleep_for (std::chrono::seconds(1));
  // cout << c << endl;
  // code here runs concurrently with foo 
  thread_handle.join();

  // You can play around with sleeping and printing this out in
  // different locations (see comments above)
  cout << c << endl;

  return 0; 
}
