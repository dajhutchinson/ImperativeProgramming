#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

void hex (int n) {
  char c[9];
  for (int k = 7; k >= 0; k --) {
    int d = (n & 0xF); // d
    if (d > 9) c[k] = (char) (d + 55);
          else c[k] = (char) (d + 48);
    n = n >> 4;
  }
  c[8] = '\0';
  printf("%s\n", c);
}

void binary (int n) {
  char c[33];
  for (int k = 31; k >= 0; k--) {
    int d = (n & 0x1);
    c[k] = (char) (d + 48);
    n = n >> 1;
  }
  c[32] = '\0';
  printf("%s\n", c);
}

int main(int n, char *args[n]) {
    if ((n == 3) && strcmp(args[1],"-h")==0) hex(atoi(args[2]));
    else if ((n == 3) && strcmp(args[1],"-b")==0) binary(atoi(args[2]));
    else printf("Use: .\\hex -b n for binary; \\hex -h n for hex\n");
    return 0;
}
