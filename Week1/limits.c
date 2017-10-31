#include <stdio.h>

int num = 42;
int it = 1000000000;
int run = 1;
int count = 0;

int main() {

  while (run == 1) {
    count += 1;
    if (num < 0) {
      num = -num - it;
      it = it/10;
      if (it == 0) {
      	run = 0;
      	printf("%i, # = %i\n", num, count);
	     }
    } else {
      num = num + it;
    }
  }

  return 0;
}
