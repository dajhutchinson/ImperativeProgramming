#include <stdio.h>

int square(int n);

int main() {
    int value = square(42);
    printf("\n%i\n", value);
    return 0;
}

int square(int n) {
  return n*n;
}
