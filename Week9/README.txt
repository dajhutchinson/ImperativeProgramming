extended.c

WHAT IS IT:
  This program adds additional functions for manipulating and traversing lists, using functions from list.c

HOW TO COMPILE:
  gcc -std=c99 -pedantic -Wall -O3 -c list.c
  gcc -std=c99 -pedantic -Wall -O3 -DmainExt=main -c extended.c
  gcc -std=c99 -pedantic -Wall -O3 list.o extended.o ext

HOW TO RUN:
  Enter either:
    ".\ext" to run the automatic tests
  Or,
    ".\ext N1 N2 N3..." where N1, N2 & N3 are non-negative integers, less than 1,000,000.
    To preform operations on these numbers, defined in run().
      Currently it creates a list with these integers and performs a linear and
      binary search for 3 and then performs an insertion sort, which is outputted.

DETAIL <list.c>:
  I developed some extra functions in list.c which I thought would be useful:
   - printForwards() = Prints the list in sequential order, first to last;
   - printBackwards() = Prints the list in sequential order, last to first;
   - count() = Returns the number of elements in a list;
   - go() = Moves pointer to a particular, numerical position in the list;
   - listFromString() = Takes in a string and returns a list that fulfils the criteria of the string.
                      = Pass single digit integers, without spaces, and place a | where the pointer should be.
                      = E.g. "1|2" returns a list contain a 1 and a 2, with the pointer between the two of them;
   - compare() = Takes in a list and a string, returning whether the list matches the criteria of the string.

DETAIL <extended.c>:
   - createList() = Creates a list with the integers the user entered;
   - bubbleSortList() = Performs a bubble sort on the list, to put items in ascending order.
                      = I like the bubble sort as it doesn't require creating another list, even though it is generally more inefficient;
   - insertionSortList() = Performs an insertion sort on the list, return a list sorted in ascending order;
   - linearSearch() = Searchs for a given item in the list, using a linear seach;
                    = It prints either the number of comparisions required to find the item,
                    = or that the item couldn't be found (i.e. It's not in the list).
   - binarySearch() = Uses the insertSortList() function to sort the list and then performs a binary search to find a given item;
                    = It prints either the number of comparisions required to find the item,
                    = or that the item couldn't be found (i.e. It's not in the list).
