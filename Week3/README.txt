sort.c

What is it:
	A program which allows the user to insert a list of positive integers and then outputs the numbers sorted
	from highest to lowest. The program performs the following algorithms:
		Insertion sort;
		Bubble sort.

How to compile:
	Enter "gcc -std=c99 -pedantic -Wall -O3 sort.c -o sort"

How to run:
	Having compiled enter either:
		"./sort" to run the programs automatic tests;
	Or:
		"./sort N1 N2 N3..." where N1,N2,N3... are positive integers less than 10000000
		To perform the sorts on N1,N2,N3...

To do:
	1) Implement more sort algorithms;
	2) Enable sorting of decimials & negative numbers.
