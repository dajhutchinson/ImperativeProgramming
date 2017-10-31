tictactoe.c

What is it:
	A program that allows to players to complete a game of tic tac toe (AKA Naughts & Crosses).
	The program verifies that a move is legal & checks if a user has won.

How to compile:
	Enter "gcc -std=c99 -pedantic - Wall -O3 tictactoe.c -o ttt" in the terminal

How to run:
	Having compiled either enter:
		"./ttt" - to begin a 3x3 game.
	Or:
		"./ttt n" - to begin a nxn game;
			  - n must be between 2 & 9, inclusive.

How to play:
	Each turn a player must enter a single number to signal in which position they wish to place their piece.
	On a 3x3 board the top-left position is number "0"; top-middle is "1"; and so on until the bottom-right is "8".

	The 3x3 board is:	The 4x4 board is:
	   [0] [1] [2]		[0]  [1]  [2]  [3]
	   [3] [4] [5]		[4]  [5]  [6]  [7]
	   [6] [7] [8]		[8]  [9]  [10] [11]
				[12] [13] [14] [15]

	(NOTE: A board is outputted to the right of the game board which shows the values for all the positions)

	After a player enters their move the program check it is a valid move (i.e. that it is a position on the board
	which doesn't have a piece in it). If the move is not valid then the same player will be allowed to re-enter another
	position, until they enter a valid move.

	If the move is valid then the piece is placed on the board and the program checks if that player has won. If they
	have then the game ends and a message is outputted stating who has one and with what construct (row, column or diagonal);
	Otherwise, the next player will be allowed to go.

	The players keep entering moves until one wins, or all positions are filled. If all position are filled then the game
	ends and a draw is declared.

To do:
	1) I want to implement functions that automatically test the program;
	2) I want to change the program to work for any board size greater than or equal to 1.
