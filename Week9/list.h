/* This is a library module supporting lists.  A list has a current position
which is thought of as being between items, and can thus be anywhere from
before the first item to after the last item.  Every operation is constant time.

The items stored in a list are of type 'item'.  The typedef for this can be
changed for any particular application so that 'item' stands for any desired
type, e.g. a raw type such as int, char[20], struct... or pointer type such as
char *, struct...*.

The lists provided by this module are not thread safe.
*/
#include <stdbool.h>

// The type of items stored in the list. Change this for different applications.
struct list;
typedef struct list list;
typedef int item;

// The list type is opaque (declared here, and defined in list.c).

// Create a new empty list.
list *newList();

// Output error messages
void fail(char* message);

// Set the current position before the first item or after the last item, e.g.
// to begin a forward or backward traversal.
void start(list *l);
void end(list *l);

// Check whether the current position is at the start or end, e.g. to test
// whether a traversal has finished.
bool atStart(list *l);
bool atEnd(list *l);
bool nearStart (list *l);
bool nearEnd (list *l);

// Move the current position one place forwards or backwards.  It is an error
// to call forward when at the end of the list, or backward when at the start.
void forward(list *l);
void backward(list *l);

// Insert an item before or after the current position (i.e. at the current
// position, but with the current position ending up after or before the new
// item).
void insertBefore(list *l, item x);
void insertAfter(list *l, item x);

// Get the item before or after the current position. It is an error to call
// getBefore when at the start, or getAfter when at the end.
item getBefore(list *l);
item getAfter(list *l);

// Set the item before or after the current position. It is an error to call
// setBefore when at the start, or setAfter when at the end.
void setBefore(list *l, item x);
void setAfter(list *l, item x);

// Delete the item before or after the current position. It is an error to call
// deleteBefore when at the start, or deleteAfter when at the end.
void deleteBefore(list *l);
void deleteAfter(list *l);

// Print all items in the list, either first to last or last to first
void printForwards(list *l);
void printBackwards(list *l);

// Returns the number of items in a list;
int count (list* l);

// Go to a particular position in the list
void go (list* l, int n);

// Used for teting
list* listFromString (char* string);
bool compare (list* l, char* string);
