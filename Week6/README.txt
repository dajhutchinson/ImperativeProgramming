four.c

WHAT IS IT:
  This is a program that allows the user to play a game of Connect-Four.

HOW TO PLAY:
  Users are given a 7x7 board to play on.
  Users take it in turn to choose a column to place their piece in.
  Columns are chosen by entering a number between [1,7] inclusive, pieces can only be placed in columns with a free space.
  If the chosen column is full, or doesn't exist the user is asked to choose again.
  Otherwise, their piece is placed in the lowest available space in their chosen column.
  Then the next player goes.
  A player wins when four of their pieces form an unbroken straight line either: horizontally, vertically or diagonally.
  If the board is filled up and no-one has one, then the game is a draw.

HOW TO COMPILE:
  Enter "gcc -std=c99 -pedantic -Wall -O3 four.c -o four"

HOW TO RUN:
  Enter either:
    ".\four" - to run the automatic tests.
 Or:
  ".\four O" - to run the game with Os starting
  ".\four X" - to run the game with Xs starting
