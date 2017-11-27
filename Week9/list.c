#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct cell cell;

struct cell {
  item data;
  cell* previous;
  cell* next;
};

struct list {
  cell* start;
  cell* position;
  cell* end;
};

// Create a new cell
cell* newCell (item value) {
  cell *new = malloc(sizeof(cell));
  new -> data = value;
  new -> previous = NULL;
  new -> next = NULL;
  return new;
}

// Create a new, blank list
list* newList () {
  list *new = malloc(sizeof(list));
  new -> start = newCell(0);
  new -> position = new -> start;
  new -> end = newCell(0);
  new -> start -> next = new -> end;
  new -> end -> previous = new -> start;
  return new;
}

// Go to a particular position in a list
void go (list* l, int n) {
  if (n > count(l) + 1) fail("Position is out of range.");
  start(l);
  for (int k = 0; k < n; k++) forward(l);
}

// Output error messages
void fail(char *message) {
  fprintf(stderr, "ERROR: %s\n", message);
  exit(1);
}

// Check if list is empty
bool isEmpty (list *l) {
  if (l -> start -> next == l -> end) return true;
  return false;
}

// Set position to start
void start (list *l) {
  l -> position = l -> start -> next;
}

// Set position to end of list
void end (list *l) {
  l -> position = l -> end;
}

// Check if position = start
bool atStart (list *l) {
  if (l -> position == l -> start) return true;
  return false;
}

// Check if position is at end
bool atEnd (list *l) {
  if (l -> position == l -> end) return true;
  return false;
}

// If within one place of end
bool nearEnd (list *l) {
  if (l -> position -> next == l -> end) return true;
  return false;
}

// If within one place of end
bool nearStart (list *l) {
  if (l -> position -> previous == l -> start) return true;
  return false;
}

// Increment position by one
void forward (list *l) {
  if (atEnd(l)) fail("Already at end of list.");
  l -> position = l -> position -> next;
}

// Decrement position by one
void backward (list *l) {
  if (atStart(l)) fail("Already at start of list");
  l -> position = l -> position -> previous;
}

// Insert a new item before current item
void insertBefore (list *l, item x) {
  cell* new = newCell(x);
  if (atStart(l)) {
    new -> next = l -> start -> next;
    new -> previous = l -> start;
  } else {
    new -> next = l -> position;
    new -> previous = l -> position -> previous;
  }
  new -> next -> previous = new;
  new -> previous -> next = new;
  l -> position = new;
}

// Insert a new item item after current item
void insertAfter (list *l, item x) {
  cell* new = newCell(x);
  if (atEnd(l)) {
    new -> next = l -> end;
    new -> previous = l -> end -> previous;
  } else {
    new -> next = l -> position -> next;
    new -> previous = l -> position;
  }
  new -> next -> previous = new;
  new -> previous -> next = new;
  l -> position = new;
}

// Return item before current position
item getBefore (list *l) {
  if (atStart(l)) fail("No items before pointer.");
  return l -> position -> previous -> data;

}

// Return item after current position
item getAfter (list *l) {
  if (atEnd(l)) fail("No items after pointer");
  return l -> position -> data;
}

// Move item to position before current
void setBefore (list *l, item x) {
  if (atStart(l) || (l -> position -> previous == l -> start)) fail("No items before pointer.");
  l -> position -> previous -> data = x;
}

// Move item to position after current
void setAfter (list *l, item x) {
  if (atEnd(l) || (l -> position == l -> end)) fail("No items after pointer.");
  l -> position -> data = x;
}

// Delete item before current position
void deleteBefore (list *l) {
  if (atStart(l) || (l -> position -> previous == l -> start)) fail("No items before pointer.");
  cell* toDelete = l -> position -> previous;
  l -> position -> previous = toDelete -> previous;
  toDelete -> previous -> next = l -> position;
  free(toDelete);
}

// Delete item after current position
void deleteAfter (list *l) {
  if (atEnd(l) || (atStart(l)) || (l -> position -> next == l -> end)) fail("No items after pointer");
  l -> position -> previous -> next = l -> position -> next;
  l -> position -> next -> previous = l -> position -> previous;
  free(l -> position);
}

// Print all items in the list, starting with the first and going forwards
void printForwards (list *l) {
  cell* p = l -> position;
  start(l);
  while (!atEnd(l)) {
    printf("%i", getAfter(l));
    if (!nearEnd(l)) printf(", ");
    forward(l);
  }
  printf("\n");
  l -> position = p;
}

// Print all items in the list, starting with the last and working back
void printBackwards (list *l) {
  cell* p = l -> position;
  end(l);
  while (!nearStart(l)) {
    printf("%i", getBefore(l));
    backward(l);
    if (!nearStart(l)) printf(", ");
  }
  printf("\n");
  l -> position = p;
}

// Count number of items in a list
int count (list* l) {
  int n = 0;
  cell* p = l -> position;
  start(l);
  while (!atEnd(l)) {
    n++;
    forward(l);
  }
  l -> position = p;
  return n;
}

// Create a list from a string, for testing
list* listFromString (char* string) {
  int len = strlen(string);
  list* l = newList();
  for (int k = 0; k < len; k++) {
    if (string[k] != '|') insertAfter(l, (item) string[k] - 48);
  }
  start(l);
  bool found = false;
  int pos = 0;
  while (found == false) {
    if (string[pos] != '|') forward(l);
    else found = true;
    pos ++;
  }
  return l;
}

// Compare a list to a string, to check nice result
bool compare (list* l, char* string) {
  int len = strlen(string);
  if (len - 1 != count(l)) return false; // If comparision string contains a different number of items to those in the list

  cell* before = l -> position -> previous;
  cell* after = l -> position -> next;

  if (atStart(l)) {
    if ((string[0] != '|') || ((item) string[1] - 48 != after -> data)) return false;
  } else if (atEnd(l)) {
    if ((string[len-1] != '|') || ((item) string[len-2] - 48 != before -> data)) return false;
  } else {
    int n = 0;
    for (int k = 0; k < len; k++) if (string[k] == '|') n = k;
    if (((item) string[n-1] - 48 != before -> data) || ((item) string[n+1] - 48 != after -> data));
  }

  cell* p = l -> position;
  start(l);
  for (int k = 0; k < len; k++) {
    if (string[k] != '|') {
      int n = getAfter(l);
      if (n != (item) string[k] - 48) {l -> position = p; return false;}
      forward(l);
  }}
  l -> position = p;
  return true;
}

// Test that the insert functions
void testInsert() {
  list* l = listFromString("|");
  insertBefore(l, 1);
  assert(compare(l, "1|") == true);
  l = listFromString("|");
  insertAfter(l, 1);
  assert(compare(l, "|1") == true);
  insertAfter(l, 3);
  assert(compare(l, "1|3") == true);
  insertBefore(l, 2);
  assert(compare(l, "12|3") == true);
}

// Test that the pointer movement functions
void testMovement() {
  list* l =listFromString("12|34");
  forward(l);
  assert(compare(l, "123|4") == true);
  backward(l);
  assert(compare(l, "12|34") == true);
  start(l);
  assert(compare(l, "|1234") == true);
  end(l);
  assert(compare(l, "1234|") == true);
}

// Test that the delete functions
void testDelete() {
  list* l = listFromString("12|34");
  deleteBefore(l);
  assert(compare(l, "1|34") == true);
  deleteAfter(l);
  assert(compare(l, "1|4") == true);
}

// Test the set functions
void testSet() {
  list* l = listFromString("1|4");
  setBefore(l, 2);
  assert(compare(l, "2|4") == true);
  setAfter(l, 3);
  assert(compare(l, "2|3") == true);
}

// Test get functions
void testGet() {
  list* l = listFromString("12|34");
  assert(getAfter(l) == 3);
  assert(getBefore(l) == 2);
}

int listMain() {
  testInsert();
  testMovement();
  testDelete();
  testSet();
  testGet();
  printf("All tests passed.\n");
  return 0;
}
