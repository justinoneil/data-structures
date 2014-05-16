list.h
======

###structs:
 * `node`
   * `int data` - the value stored in thi list element
   * `struct node *next` - pointer to the next node

Any node can be treated as a list head, but be careful not to lose track of the `true` head or leave a dangling pointer.

list.c
======

###functions:
 * `struct node *listnew(int)` - dynamically allocates a new list with int number of elements.
 * `struct node *listcopy(struct node *)` - dynamically allocates a new list with data copied the argument.
 * `void listfree(struct node *)` - frees all of the element linked from struct node *, including itself.
 * `void listappend(struct node *, struct node *)` - links the second list to the end of the first list.
 * `void listappendcopy(struct node *, struct node *)` - links a copy of the second list to the end of the first list.
 * `void listinsert(struct node *, int, struct node *)` - links the second list to the first list before position int.  Link the rest of the first list to the end of the second list.
 * `void listinsertcopy(struct node *, int, struct node *)` - inserts a copy of the second list in the second list at position int.
 * `size_t listsize(struct node *)` - returns the number of elements in the list.
 * `int listgetdata(struct node *, int)` - returns the data in the list at postition int.
 * `void listsetdata(struct node *, int, int)` - sets the data in the list at the first int postition to the second int data.
 * `struct node *listdelelem(struct node *, int)` - unlinks and frees the node at postition int from the list.  Returns the head pointer for cases when you want to delete the first element from a list.