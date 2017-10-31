/* Custom versions of standard string functions. */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

// Find the length of a string, assuming it has a null terminator (like strlen).
int length(const char s[]) {
  int run = 1;
  int count = 0;
  while (run) {
    char c = s[count];
    if (c == '\0') {
      run =0;
    } else {
      count ++;
    }
  }
  return count;
}

// Copy string s into the character array t (like strcpy).
void copy(char t[], const char s[]) {
  int n = length(s);
  for (int k = 0; k < n; k ++) {
    t[k] = s[k];
  }
  t[n] = '\0';
}

// Compare two strings, returning negative, zero or positive (like strcmp).
int compare(const char s[], const char t[]) {
  int lens = length(s);
  int lent = length(t);

  int count = 0;
  while ((count < lens) || (count < lent)) {
    char cs = s[count];
    char ct = t[count];
    if (cs == ct) {count ++; continue;}
    int is = (int) cs;
    int it = (int) ct;
    if (is > it) return 1;
    return -1;
  }
  return 0;
}

// Join string s to the end of string t (like strcat).
void append(char t[], const char s[]) {
  int lens = length(s);
  int lent = length(t);
  for (int k = 0; k < lens; k++ ) {
    t[k+lent] = s[k];
  }
  t[lent+lens] = '\0';
}

// Find the (first) position of s in t, or return -1 (like strstr).
int find(const char t[], const char s[]) {
    int lens = length(s);
    int lent = length(t);
    int position = -1;
    int c, k = 0;
    int go = 1;

    while ((k < lent) && (go == 1)) {
      c = 0;
      while (c < lens) {
        if ((t[c+k] == s[c]) && c == lens-1) {
          position = k;
          go = 0;
          break;
        }
        c++;
      }
      k++;
      c = 0;
    }
    return position;
}

// -----------------------------------------------------------------------------
// Tests and user interface

// Tests 1 to 5
void testLength() {
    assert(length("") == 0);
    assert(length("c") == 1);
    assert(length("ca") == 2);
    assert(length("cat") == 3);
    char s[] = "dog";
    assert(length(s) == 3);
}

// Tests 6 to 9
void testCopy() {
    char t[10];
    copy(t, "cat");
    assert(t[0] == 'c' && t[1] =='a' && t[2] == 't' && t[3] =='\0');
    copy(t, "at");
    assert(t[0] == 'a' && t[1] =='t' && t[2] =='\0');
    copy(t, "t");
    assert(t[0] == 't' && t[1] =='\0');
    copy(t, "");
    assert(t[0] == '\0');
}

// Tests 10 to 17
void testCompare() {
    assert(compare("cat", "dog") < 0);
    assert(compare("dog", "cat") > 0);
    assert(compare("cat", "cat") == 0);
    assert(compare("an", "ant") < 0);
    assert(compare("ant", "an") > 0);
    assert(compare("", "a") < 0);
    assert(compare("a", "") > 0);
    assert(compare("", "") == 0);
}

// Tests 18 to 20
void testAppend() {
    char t[10] = "cat";
    append(t, "");
    assert(t[0] == 'c' && t[1] =='a' && t[2] == 't' && t[3] =='\0');
    t[2] = '\0';
    append(t, "t");
    assert(t[0] == 'c' && t[1] =='a' && t[2] == 't' && t[3] =='\0');
    t[0] = '\0';
    append(t, "cat");
    assert(t[0] == 'c' && t[1] =='a' && t[2] == 't' && t[3] =='\0');
}

// Tests 21 to 25
void testFind() {
    assert(find("cat", "cat") == 0);
    assert(find("cat", "c") == 0);
    assert(find("cat", "t") == 2);
    assert(find("cat", "x") == -1);
    assert(find("banana", "an") == 1);
}

// Test the functions.
int main() {
    testLength();
    testCopy();
    testCompare();
    testAppend();
    testFind();
    printf("Tests all pass.\n");
    return 0;
}
