#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "list.h"

// Converts string to an integer
item strToItem(char* str) {
  item n = 0;
  for (int k = 0; k < strlen(str); k++) {
    int m = (int) str[k] - 48;
    int i = strlen(str) - k;
    while (i > 1) {m = m * 10; i--;}
    n += m;
  }
  return n;
}

// Create a list from the users input
list* createList(int n, char* args[n]) {
  list* l = newList();
  for (int k = 1; k < n; k++) {
    insertAfter(l, strToItem(args[k]));
  }
  return l;
}

// Sort list using a bubble sort
void bubbleSortList(list* l) {
  bool change = true;
  while (change == true) {
    change = false;
    start(l);
    while (!nearEnd(l)) {
      item current = getAfter(l);
      forward(l);
      item next = getAfter(l);
      if (next < current) {
        setBefore(l, next);
        setAfter(l, current);
        change = true;
}}}}

// Sort list using an insertion sort
list* insertionSortList(list* l) {
  list* sorted = newList();
  start(l);
  insertAfter(sorted, getAfter(l));
  forward(l);
  while(!atEnd(l)) {
    start(sorted);
    while(!atEnd(sorted) && (getAfter(sorted) < getAfter(l))) {
      forward(sorted);
    }
    insertBefore(sorted, getAfter(l));
    forward(l);
  }
  return sorted;
}

// Use linear search to find an item in a list
void linearSearch(list* l, item n, bool test) {
  int count = 0;
  bool found = false;
  start(l);
  while (!atEnd(l) && (found == false)) {
    count ++;
    if (getAfter(l) != n) forward(l);
    else found = true;
  }
  if (!test) {
    if (found && (count != 1)) printf("Linear search found %i after %i comparisions.\n", n, count);
    else if (found) printf("Linear search found %i after %i comparision.\n", n, count);
    else printf("%i not found.\n", n);}
}

// Use binary search to find an item in a list
list* binarySearch(list* l, item n, bool test) {
  l = insertionSortList(l);
  int op = 0;
  int lower = 0; int upper = count(l);
  bool found = false;
  while ((lower <= upper) && (!found) && (lower != count(l))) {
    op++;
    int mid = (lower + upper) / 2;
    start(l);
    go(l, mid);
    if (getAfter(l) == n) found = true;
    else if (getAfter(l) < n) lower = mid + 1;
    else upper = mid - 1;
  }
  if (!test) {
    if (found && (op != 1)) printf("Binary search found %i after %i comparisions.\n", n, op);
    else if (found) printf("Binary search found %i after %i comparision.\n", n, op);
    else printf("%i not found.\n", n);}
  return l;
}

// Check
bool checkValid(int n, char* array[n]) {
  for (int k = 1; k < n; k++) {
    if ((strlen(array[k]) > 7) || (strlen(array[k]) == 0)) return false;
    for (int i = 0; i < strlen(array[k]); i++) {
      if (((int) array[k][i] < 48) || ((int) array[k][i] > 57)) return false;
  }}
  return true;
}

// Test sorting algorithms
void testSort() {
  // Test bubbleSortList()
  list* l = listFromString("12345|");
  bubbleSortList(l);
  assert(compare(l, "12345|") == true);
  l = listFromString("15243|");
  bubbleSortList(l);
  assert(compare(l, "12345|") == true);
}

// Test seach algorithms
void testSearch() {
  // Test linearSearch()
  list* l = listFromString("12345|");
  linearSearch(l,3,true);
  assert(compare(l, "12|345") == true);
  l = listFromString("12345|");
  linearSearch(l,6,true);
  assert(compare(l, "12345|") == true);
  l = listFromString("54321|");
  linearSearch(l,3,true);
  assert(compare(l, "54|321") == true);

  // Test binarySearch()
  l = listFromString("12345|");
  l = binarySearch(l,3,true);
  assert(compare(l, "12|345") == true);
  l = listFromString("12345|");
  l = binarySearch(l,6,true);
  assert(compare(l, "12345|") == true);
  l = listFromString("15243|");
  l = binarySearch(l,3,true);
  assert(compare(l, "12|345") == true);
}

// Test strToItem()
void testStrToItem() {
  assert(strToItem("1") == 1);
  assert(strToItem("123456") == 123456);
  assert(strToItem("0") == 0);
}

// Test checkValid() function
void testValid() {
  char* a1[2] = {"", ""}; assert(checkValid(2, a1) == false);
  char* a2[2] = {"", "1"}; assert(checkValid(2, a2) == true);
  char* a3[2] = {"", "a"}; assert(checkValid(2, a3) == false);
  char* a4[5] = {"", "a", "1", "2", "3"}; assert(checkValid(5, a4) == false);
  char* a5[5] = {"", "1", "2", "3", "4"}; assert(checkValid(5, a5) == true);
}

// Run Tests
void test() {
  testValid();
  testStrToItem();
  testSort();
  testSearch();
  printf("All Tests Passed!\n");
}

// Run program
void run(int n, char* args[n]) {
  list* l = createList(n, args);
  printForwards(l);
  linearSearch(l, 3,false);
  binarySearch(l, 3,false);
  printf("Sorted list - ");
  printForwards(insertionSortList(l));
}

int mainExt(int n, char* args[n]) {
  if (n == 1) {
    test();
    return 0;
  } else {
    if (checkValid(n, args)) {
      run(n, args);
    } else {
      printf("Only enter integers between 0 and 1,000,000.\n");
  }}
  return 0;
}
