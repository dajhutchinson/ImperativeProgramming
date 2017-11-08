 /*
 *  Four in a row game
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>
 #include <string.h>
 #include <assert.h>

 enum player { X, O, N };
 typedef enum player player;

 enum validity { Unchecked, OK, BadFormat, BadDigit, BadCell };
 typedef enum validity validity;

struct game {
  player board[7][7];
  player next;
  int moves;
};

// Set up new game
void newGame (struct game *g, player p) {
  for (int y = 0; y < 7; y++) {
    for (int x = 0; x < 7; x++) {
      g -> board[y][x] = N;
  }}
  g -> next = p;
  g -> moves = 0;
}

// Converts a player datatype to a char
char show (player p) {
  char c[3]; c[0] = 'X'; c[1] = 'O'; c[2] = ' ';
  return c[p];
}

// Outputs board to user
void output (struct game *g) {
  for (int y = 0; y < 7; y++) {
    for (int x = 0; x < 7; x++) {
      printf("[%c] ", show(g -> board[y][x]));
    }
    printf("\n");
}}

int valid(int col, struct game *g) {
  if (g -> board[0][col] == N) {
    return 0;
  } else {
    return -1;
  }
}

// Verify inputted is valid, and move is legal
validity verify (char *text, struct game *g) {
  if ((strlen(text) != 1) && (text[1] != '\n')) {
    return BadFormat;
  } else if ((( (int) text[0] - 48) < 1) || (( (int) text[0] - 48) > 7)) {
    return BadDigit;
  } else if (valid((int) text[0] - 49, g) == -1) {
    return BadCell;
  } else {
    return OK;
  }
}

void outputError (validity v) {
  if (v == BadFormat) printf("Enter a single digit between [1-7] inclusive.\n");
  else if (v == BadDigit) printf("Enter a single digit between [1-7] inclusive.\n");
  else if (v == BadCell) printf("That column is full. Please choose another one.\n");
}

// Mave move
void move (int col, struct game *g) {
  for (int y = 6; y > -1; y--) {
    if (g -> board[y][col - 1] == N) {
      g -> board[y][col - 1] = g -> next;
      g -> moves ++;
      if (g -> next == X) g -> next = O;
      else g -> next = X;
      return;
}}}

// Check if a player has won
player win (struct game *g) {
  // Check Rows
  for (int y = 0; y < 7; y++) {
    for (int x = 0; x < 4; x ++) {
      if ((g -> board[y][x] != N) && (g -> board[y][x] == g -> board[y][x+1]) && (g -> board[y][x] == g -> board[y][x+2]) && (g -> board[y][x] == g -> board[y][x+3])) {
        return g -> board[y][x];
  }}}

  // Check Columns
  for (int x = 0; x < 7; x++) {
    for (int y = 0; y < 4; y ++) {
      if ((g -> board[y][x] != N) && (g -> board[y][x] == g -> board[y+1][x]) && (g -> board[y][x] == g -> board[y+2][x]) && (g -> board[y][x] == g -> board[y+3][x])) {
        return g -> board[y][x];
  }}}

  // Check Diagonals
  // Bottom left to top right
  for (int y = 3; y < 7; y ++) {
    for (int x = 0; x < 4; x ++) {
      if ((g -> board[y][x] != N) && (g -> board[y][x] == g -> board[y-1][x+1]) && (g -> board[y][x] == g -> board[y-2][x+2]) && (g -> board[y][x] == g -> board[y-3][x+3])) {
        return g -> board[y][x];
  }}}

  // Top Left to Bottom right
  for (int y = 0; y < 4; y ++) {
    for (int x = 0; x < 4; x ++) {
      if ((g -> board[y][x] != N) && (g -> board[y][x] == g -> board[y+1][x+1]) && (g -> board[y][x] == g -> board[y+2][x+2]) && (g -> board[y][x] == g -> board[y+3][x+3])) {
        return g -> board[y][x];
  }}}

  return N;
}

// Check if the game has been drawn
int draw (struct game *g) {
  if ((g -> moves == 49) && (win(g) == N)) return 1;
  return -1;
}

// Asks for column
int ask (struct game *g) {
  char line[100];
  printf("%c\'s turn\n", show(g -> next));
  if (fgets(line, 100, stdin) != NULL) {
    if (verify(line, g) == OK) {
      return (int) line[0] -48;
    } else {
      outputError(verify(line, g));
    }
  }
  return -1;
}

// Play the game
void play (player p) {
  struct game g; bool run = true;
  newGame(&g, p);
  output(&g);
  while (run) {
    int col = ask(&g);
    if (col != -1) {
      move(col, &g);
      output(&g);
      if(win(&g) != N) {
        printf("Player %c wins!\n", show(win(&g)));
        run = false;
      } else if (draw(&g) == 1) {
        printf("It's a draw\n");
        run = false;
}}}}

void testShow () {
  assert((show(X)) == 'X');
  assert((show(O)) == 'O');
  assert((show(N)) == ' ');
}

void testVerify (struct game *g) {
  *g = (struct game) {{{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N}},N,0};
  assert((verify("1", g)) == OK);
  assert((verify("7", g)) == OK);
  assert((verify("0", g)) == BadDigit);
  assert((verify("8", g)) == BadDigit);
  assert((verify("a", g)) == BadDigit);
  assert((verify("a1", g)) == BadFormat);
  *g = (struct game) {{{O,O,O,O,O,O,O},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N}},N,0};
  assert((verify("1", g)) == BadCell);
}

void testMove (struct game *g) {
  *g = (struct game) {{{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N}},O,0};
  move (1, g);
  assert(g -> board[6][0] == O);
  assert(g -> next == X);
  assert(g -> moves == 1);
  *g = (struct game) {{{N,N,N,N,N,N,N},{O,N,N,N,N,N,N},{O,N,N,N,N,N,N},{O,N,N,N,N,N,N},{O,N,N,N,N,N,N},{O,N,N,N,N,N,N},{O,N,N,N,N,N,N}},X,10};
  move (1, g);
  assert(g -> board[0][0] == X);
  assert(g -> next == O);
  assert(g -> moves == 11);

}

void testWin (struct game *g) {
  *g = (struct game) {{{O,O,O,O,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N}},O,0};
  assert(win(g) == O);
  *g = (struct game) {{{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,X,X,X,X}},O,0};
  assert(win(g) == X);
  *g = (struct game) {{{O,N,N,N,N,N,N},{O,N,N,N,N,N,N},{O,N,N,N,N,N,N},{O,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N}},O,0};
  assert(win(g) == O);
  *g = (struct game) {{{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,X},{N,N,N,N,N,N,X},{N,N,N,N,N,N,X},{N,N,N,N,N,N,X}},O,0};
  assert(win(g) == X);
  *g = (struct game) {{{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,O},{N,N,N,N,N,O,N},{N,N,N,N,O,N,N},{N,N,N,O,N,N,N}},O,0};
  assert(win(g) == O);
  *g = (struct game) {{{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,X,N,N,N},{N,N,N,N,X,N,N},{N,N,N,N,N,X,N},{N,N,N,N,N,N,X}},O,0};
  assert(win(g) == X);
  *g = (struct game) {{{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N}},O,0};
  assert(win(g) == N);
  *g = (struct game) {{{N,N,N,N,X,X,X},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N}},O,0};
  assert(win(g) == N);
  *g = (struct game) {{{N,N,N,N,N,N,X},{N,N,N,N,N,N,X},{N,N,N,N,N,N,X},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N}},O,0};
  assert(win(g) == N);
  *g = (struct game) {{{X,N,N,N,N,N,N},{N,X,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,X,N},{N,N,N,N,N,N,X}},O,0};
  assert(win(g) == N);
}

void testDraw (struct game *g) {
  *g = (struct game) {{{O,X,O,X,O,X,O},{X,O,X,O,X,O,X},{X,O,X,O,X,O,X},{X,O,X,O,X,O,X},{O,X,O,X,O,X,O},{O,X,O,X,O,X,O},{O,X,O,X,O,X,O}},O,49};
  assert(draw(g) == 1);
  *g = (struct game) {{{N,X,O,X,O,X,O},{X,O,X,O,X,O,X},{X,O,X,O,X,O,X},{X,O,X,O,X,O,X},{O,X,O,X,O,X,O},{O,X,O,X,O,X,O},{O,X,O,X,O,X,O}},O,48};
  assert(draw(g) == -1);
  *g = (struct game) {{{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N},{N,N,N,N,N,N,N}},N,0};
  assert(draw(g) == -1);
}
// Automatic testing of program
void test () {
  struct game *g = malloc(sizeof(struct game));
  testShow();
  testVerify(g);
  testMove(g);
  testWin(g);
  testDraw(g);
  free (g);
  printf("All tests passed.\n");
}

int main(int n, char *args[n]) {
  if (n == 1) test();
  else if ((n == 2) && (strcmp(args[1],"X") == 0)) play(X);
  else if ((n == 2) && (strcmp(args[1],"O") == 0)) play(O);
  else printf("Use either: ./four to run tests; or, ./oxo [O, X] to play the game.\n");
}
