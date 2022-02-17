#include <atomic>
#include <iostream>
using namespace std;

typedef struct { int x, y; } two_ints_struct;

typedef struct { int x, y, z, w; } four_ints_struct;

int main() {
  atomic<int> a_int;

  atomic<float> a_float;

  atomic<two_ints_struct> a_tis;

  atomic<four_ints_struct> a_fis;

  atomic<four_ints_struct*> a_fisp;
  
  cout << "is atomic int lock free? " << a_int.is_lock_free() << endl;

  cout << "is atomic float lock free? " << a_float.is_lock_free() << endl;

  cout << "is atomic two_ints_struct lock free? " << a_tis.is_lock_free() << endl;

  cout << "is atomic four_ints_struct lock free? " << a_fis.is_lock_free() << endl;

  cout << "is atomic four_ints_struct pointer lock free? " << a_fisp.is_lock_free() << endl;
  
  return 0;
}
