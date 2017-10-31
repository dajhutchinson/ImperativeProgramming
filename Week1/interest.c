#include <stdio.h>

int add(double n, double p);

int main() {
  double n = add(1000.0, 2.7);
  printf("%f\n", n);
  return 0;
}

int add(double n, double p) {
  //double interest = n*(p/100);
  double total = n + n * (5.0 / 100.0);
  return total;
}
