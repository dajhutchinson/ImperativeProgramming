GCC = gcc -std=c99 -pedantic -Wall -O3

rlist: list.c list.h
	$(GCC) -DlistMain=main list.c -o list
	./list

clist: list.c list.h
	$(GCC) -DlistMain=main list.c -o list

rext: extended.c list.c list.h
	$(GCC) -c list.c
	$(GCC) -c extended.c
	$(GCC) list.o extended.o -o ext
	./ext

cext: extended.c list.c list.h
	$(GCC) -c list.c
	$(GCC) -DmainExt=main -c extended.c
	$(GCC) list.o extended.o -o ext
