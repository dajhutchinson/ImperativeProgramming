/*
 * Compile:
 *  "make csort"; or,
 *  "gcc -std=c99 -pedantic -Wall -O3 sort.c -o sort"/
 *
 * Run:
 *  "./sort" to run tests
 *  "./sort N1 N2 N3..." where N1,N2,N3... are positive integers less than 10000000
 *
 * A program to sort an array of integers using different methods:
 *    Insertion sort
 *    Bubble Sort
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// Convert arrays to strings so that they can be printed
char *arrayToString(int n, int array[n]) {
  static char string[100];
  // Empty out string
  int i = 0;
  while(string[i] != '\0') {
      string[i] = '\0';
      i++;
  }
  // Inialise new string
  string[0] = '[';
  for (int k = 0; k < n-1; k++) { // Add values to string
    char temp[10] = "";
    sprintf(temp, "%i,", array[k]);
    strcat(string, temp);
  }
  char temp[10] = "";
  sprintf(temp, "%i]", array[n-1]);// Add last value to string, and close
  strcat(string, temp);
  return string;
}

// Complete an insertion sort
char *insertion(const int n, const int unsorted[n]) {
  int sorted[n+1];
  for (int k = 0; k < n+1; k++) sorted[k] = 0;
  for (int k = 0; k < n; k++) { // Check every element in unsorted[]
    int value = unsorted[k]; // Map value from unsorted[]
    for (int j = 0; j <= k; j++) { // Run through all filled values in sorted (and one more), largest to smallest
      if (value > sorted[j]) { // If unsorted value is greater than, sorted value in position
        for (int i = n; i >= j; i--){
          sorted[i+1] = sorted[i]; // Shift all subsequent values to the right, to make space for new value
        }
        sorted[j] = value; // Insert new value
        break;
  }}}
  char *string = arrayToString(n, sorted); // Convert array to string
  return string;
}

// Complete a bubble sort
char *bubble(const int n, int unsorted[n]) {
  bool run = true; // Check for sorts while true
  while (run) {
    run = false; // Set to false, only set to true if a change is made
    for (int k = 0; k < n-2; k++) { //Compare all adjacent pairs
      int a = unsorted[k];
      int b = unsorted[k+1];
      if (b > a) { // If second value is greater than first, swap them
        run = true;
        unsorted[k] = b;
        unsorted[k+1] = a;
  }}}
  char *string = arrayToString(n-1, unsorted); // Convert array to string
  return string;
}

// Check that user has only entered integers
int checkValid(int n, char *array[n]) {
  for (int k = 1; k < n; k++) { // Check every element in array
    if (strlen(array[k]) > 7) return 1; // If number is >= 10000000 return false
    for (int i = 0; i < strlen(array[k]); i++){ // Check every character of element
      int ascii = (int) array[k][i];
      if ((ascii < 48) || (ascii > 57)) return 1; // If character is not a digit return false
  }}
  return 0;
}

// Run tests
int test() {
  // Test arrayToString()
  int a0[4] = {1,2,3,4}; if (strcmp(arrayToString(4, a0), "[1,2,3,4]") != 0) {printf("Failed test 0\n"); return 1;}

  // Test insertion()
  int a1[4] = {4,3,2,1}; if (strcmp(insertion(4,a1), "[4,3,2,1]") != 0) {printf("Failed test 1\n"); return 1;}
  int a2[4] = {1,2,3,4}; if (strcmp(insertion(4,a2), "[4,3,2,1]") != 0) {printf("Failed test 2\n"); return 1;}
  int a3[4] = {2,1,4,3}; if (strcmp(insertion(4,a3), "[4,3,2,1]") != 0) {printf("Failed test 3\n"); return 1;}
  int a4[4] = {9999999,9999998,9999997,0}; if (strcmp(insertion(4,a4), "[9999999,9999998,9999997,0]") != 0) {printf("Failed test 4\n"); return 1;}
  int a5[4] = {0,0,0,0}; if (strcmp(insertion(4,a5), "[0,0,0,0]") != 0) {printf("Failed test 5\n"); return 1;}

  // Test bubble()
  if (strcmp(bubble(5,a1), "[4,3,2,1]") != 0) {printf("Failed test 6\n"); return 1;}
  if (strcmp(bubble(5,a2), "[4,3,2,1]") != 0) {printf("Failed test 7\n"); return 1;}
  if (strcmp(bubble(5,a3), "[4,3,2,1]") != 0) {printf("Failed test 8\n"); return 1;}
  if (strcmp(bubble(5,a4), "[9999999,9999998,9999997,0]") != 0) {printf("Failed test 9\n"); return 1;}
  if (strcmp(bubble(5,a5), "[0,0,0,0]") != 0) {printf("Failed test 10\n"); return 1;}

  // Test checkValid()
  char *a6[2] = {"", "1"}; assert(checkValid(2, a6) == 0);
  char *a7[2] = {"", "a"}; assert(checkValid(2, a7) == 1);
  char *a8[2] = {"", "5a"}; assert(checkValid(2, a8) == 1);
  char *a9[2] = {"", "5.1"}; assert(checkValid(2, a9) == 1);
  char *a10[2] = {"", "0"}; assert(checkValid(2, a10) == 0);
  char *a11[2] = {"", "9"}; assert(checkValid(2, a11) == 0);
  char *a12[2] = {"", "1234567"}; assert(checkValid(2, a12) == 0);
  char *a13[2] = {"", "10000000"}; assert(checkValid(2, a13) == 1);
  char *a14[2] = {"", "9999999"}; assert(checkValid(2, a14) == 0);

  printf("Passed all tests!\n");
  return 0;
}

// Run sort algorithms
int run(int n, int array[n]) {
  char *str0 = arrayToString(n-1, array); printf("Unsorted: %s\n", str0); // Output unsorted array
  char *str1 = insertion(n-1, array); printf("Insertion: %s\n", str1); // Output sorted array after insertion sort
  char *str2 = bubble(n, array); printf("Bubble: %s\n", str2); // Output sorted array after bubble sort
  return 0;
}

int main(int n, char *args[n]) {
    if (n == 1) { // If './sort' was entered, perform tests
      test();
      return 0;
    } else {
        int valid = checkValid(n, args); // Check user entered numbers
        if (valid == 0) { // If user only entered numbers
          int unsorted[n-1]; // Create array to store unsorted numbers
          for (int k = 1; k < n; k++) { // Fill array with zeros
            unsorted[k-1] = 0;
            unsorted[k-1] = atoi(args[k]);
          }
          run(n, unsorted); // Run sort algorithms
        } else { // If user didn't only enter numbers
          printf("Only enter integers less than 10000000.\n");
    }}
    return 0;
}
