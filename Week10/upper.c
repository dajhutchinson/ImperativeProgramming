#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

char* toUpper(int n, char* s) {
  char* string = malloc(sizeof(char) * n);
  for (int k = 0; k < n; k++) {
    char c = s[k];
    if (('a' <= c) && (c <= 'z')) string[k] = c + 'A' - 'a';
    else string[k] = c;
  }
  return string;
}

int main() {
  int max = 1000;
  char* line = malloc(sizeof(char) * max);
  FILE *in = fopen("data/in.txt", "r");
  FILE *out = fopen("data/out.txt", "w");
  fgets(line, max, in);
  while (! feof(in)) {
    fprintf(out, toUpper(strlen(line), line));
    fgets(line, max, in);
  }
  fclose(in);
  fclose(out);
  return 0;
}
