/*
 * Play tictactoe with a friend
 *
 * TO DO:
 *  Tests
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>


//2d array to store current board state
//0 = available; 1 = naughts; 2 = crosses
int board [9][9] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
int player = 1;             // Current Player
bool run = true;            // Controls if game runs
int turn = 1;               // Turn counter
int size;                   // Size of board

//Declaration of functions
int printBoard ();
int printGuide (int y);
char piece (int n);
int enterMove ();
int move ();
bool checkInput (char c[]);
bool checkMove (int m);
bool makeMove (int m);
bool checkWin();
bool checkRows();
bool checkColumns();
bool checkDiagonals();
bool test();
bool testBoard();

//Runs program
int main (int n, char *args[n]) {
  if (n == 1) {
    size = 3;
    printBoard ();
    while (run) {
      move();
    }
  } else if (n == 2) {
    if (strlen(args[1]) != 1) {
      printf("Enter a number between 2-9\n");
    } else {
      int ascii = (int) args[1][0];
      if ((ascii < 50) || (ascii > 57)) {
        printf("Enter a number between 2-9\n");
      } else {
        size = atoi(args[1]);
        printBoard ();
        while (run) {
          move();
        }
      }
    }
  } else {
    printf("Use either: ./ttt; or /ttt [1-9].\n");
  }
  return 0;
}

//Outputs the board in terminal
int printBoard () {
  printf("It is Player %i's turn.\n", player);
  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      char p = piece (board[y][x]);
      printf("[%c] ", p);
    }
    printGuide(y);
    printf("\n");
  }
  return 0;
}

// Outputs the position names for the user
int printGuide (int y) {
  printf("                    ");
  for (int k = 0; k < size; k++) {
    printf("[%i] ", (size*y) + k);
  }
  return 0;
}

//Identifies which piece to output in terminal
char piece(int n) {
  if (n == 0) {
    return '-';
  } else if (n == 1) {
    return 'O';
  } else if (n == 2){
    return 'X';
  } else {
    return ' ';
  }
}

//Runs a player's turn
int move() {
  int move = enterMove();
  bool go = checkMove(move);
  printBoard();
  if (go == true) {
    checkWin();
    if (turn == (size*size)) {
      printf("It is a Draw!\n");
      run = false;
    }
    turn++, player = (player == 1) ? 2: 1;  // Change player
  } else {
    printf("Position: %i is already occupied!\n", move);
  }
  return 0;
}

//Allows the use to enter the position they wish to place their piece in, and checks if the input is valid
int enterMove() {
  char c[100];
  bool run = true;
  while (run == true) {
    printf("Position: ");
    if (scanf("%s", c) == 1) {
      bool go = checkInput(c);
      if (go == true) {
        run = false;
      }
  }}
  printf("-------------------------------------------\n");
  return atoi(c);
}

//Returns whether or not the entered text is a number between 0-8
bool checkInput (char c[]) {
  for (int l = 0; l < strlen(c); l++) {
    int ascii = (int) c[l];
    if ((ascii < 48) || (ascii > 57)) {
      printf("Enter a number between 0-%i.\n",(size*size)-1);
      return false;
    }
  }

  int value = atoi(c);
  if ((value > -1) && (value < (size * size))) {
    return true;
  } else {
    printf("Enter a number between 0-%i.\n",(size*size)-1);
    return false;
  }
}

//Checks if select space is available to place piece in (i.e. it's current value is '0')
bool checkMove (int m) {
  if (board[m/size][m%size] == 0) {               // If space is available
    board[m/size][m%size] = player;               // Place piece
    return true;
  } else {
    return false;
  }
}

// Check if player has won
bool checkWin() {
  bool win = false;
  //Check rows
  win = checkRows();
  if (win == false) {
    //Check Columns
    win = checkColumns();
    if (win == false) {
      //Check Diagonals
      win = checkDiagonals();
  }}
  return win;
}

// Checks if any row contains only one type of piece
bool checkRows() {
  for (int y = 0; y < size; y++) {
    bool win = true;
    int player = -1;
    for (int x = 0; x < size; x++) {
      if (x == 0 && board[y][x] != 0) { player = board[y][x]; }
      if (player != board[y][x]) { win = false; }
    }
    if (win == true) {
      printf("Player %i Wins!! With a Row on line %i!\n", player, y);
      run = false;
      return true;
    }
  }
  return false;
}

//Checks if any column contains only one type of piece
bool checkColumns() {
  for (int x = 0; x < size; x++) {
    bool win = true;
    int player = -1;
    for (int y = 0; y < size; y++) {
      if (y == 0 && board[y][x] != 0) { player = board[y][x]; }
      if (player != board[y][x]) { win = false; }
    }
    if (win == true) {
      printf("Player %i Wins!! With a Column in Column %i!\n", player, x);
      run = false;
      return true;
    }
  }
  return false;
}

//Checks if any diagonals contains only one type of piece
bool checkDiagonals() {
  int y = 0, x = 0, player = -1;
  bool win = true;
  // Top-Left -> Bottom-Right
  while (x < size) {
    if ((y == 0) && (board[y][x] != 0)) { player = board[y][x]; }
    if (player != board[y][x]) { win = false;}
    y++, x++;
  }
  if (win == true) {
    printf("Player %i Wins!! With a Diagonal!\n", player);
    run = false;
    return true;
  }
  //Bottom-Left -> Top-Right
  y = size - 1, x= 0, player = -1, win = true;
  while (x < size) {
    if ((y == size - 1) && (board[y][x] != 0)) { player = board[y][x];}
    if (player != board[y][x]) { win = false;}
    y--, x++;
  }
  if (win == true) {
    printf("Player %i Wins!! With a Diagonal!\n", player);
    run = false;
    return true;
  }
  return false;
}

//TO DO
//Run all tests
bool test () {
  return false;
}

//TO DO
//Test that board outputs correctly
bool testBoard () {
  return false;
}
