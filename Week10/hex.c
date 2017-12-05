#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

/*
void hex(int n, unsigned char ) {
  for (int k = 7; k >= 0; k --) {
    int d = (n & 0xF); // d
    if (d > 9) s[k] = (char) (d + 55);
          else s[k] = (char) (d + 48);
    n = n >> 4;
  }
  s[8] = '\0';
}
*/

int main() {
  FILE *in = fopen("data/hex.txt", "rb");
  unsigned char b = fgetc(in);
  while (! feof(in)) {

    b = fgetc(in);
  }
  fclose(in);
  return 0;
}
