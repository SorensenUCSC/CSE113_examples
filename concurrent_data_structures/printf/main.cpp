#include <stdio.h>
using namespace std;

#define ITERATIONS (16)
#define INNER_ITERATIONS (1024*256)

int main() {

  for (int i = 0; i < ITERATIONS; i++) {
    for (int j = 0; j < INNER_ITERATIONS; j++) {      
      printf("x");
      //fflush(stdout);
    }
    printf("\n");
  }

  return 0;
}
