GCC = gcc -std=c99 -pedantic -Wall -O3

rtest: test.c
	$(GCC) test.c -o test
	./test
