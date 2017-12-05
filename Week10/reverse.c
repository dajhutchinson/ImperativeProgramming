#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

char* reverse (int len, char* string) {
  char* rev = malloc(sizeof(char) * len);
  for (int k = 0; k < len; k++) rev[k] = string[len - (k + 1)];
  return rev;
}

int main() {
  int max = 100; bool run = true;
  char* s = malloc(sizeof(char) * max);
  while(run){
    printf("> ");
    if (fgets(s, max, stdin) != NULL) {
      if (strcmp(".\n", s) == 0) run = false;
      else printf("%s\n", reverse(strlen(s) - 1, s));
    }
  }
  free(s);
  return 0;
}
