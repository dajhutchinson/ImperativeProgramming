#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

void hex (int n) {
  char c[9] = "00000000";
  for (int k = 7; k >= 0; k --) {
    int d = (n & 0xF); // d
    if (d > 9) c[k] = (char) (d + 55);
          else c[k] = (char) (d + 48);
    n = n >> 4;
  }
  c[8] = '\0';
  printf("\n%s\n", c);
}

int main(int n, char *args[n]) {
    if (n == 2) hex(atoi(args[1]));
    else printf("Use: .\\hex n\n");
    return 0;
}
