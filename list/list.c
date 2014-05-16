#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/***************************************************************
 * Allocate a new list with n elements and initialize data to 0.
 ***************************************************************/
struct node *listnew(size_t n) {
  if (n == 0)
    return NULL;

  struct node *head = (struct node *)malloc(sizeof(struct node));
  head->data = 0;
  head->next = listnew(n-1);
  return head;
}

/*********************************************************************
 * Create a deep copy of a list.  It would be bad to call this without
 * keeping track of the result.  Only you can prevent memory leaks.
 *********************************************************************/
struct node *listcopy(const struct node *head) {
  if (head == NULL)
    return NULL;

  struct node *newlist = (struct node *)malloc(sizeof(struct node));
  newlist->data = head->data;
  newlist->next = listcopy(head->next);
  return newlist;
}
  
/***********************************************************
 * Deallocate a list.  Remember to set your pointer to NULL.  
 ***********************************************************/
void listfree(struct node *head) {
  if (head->next != NULL)
    listfree(head->next);
  free(head);
}

/********************************************************************
 * Link tail to the end of head (be careful about using tail from now
 * on, it is part of the chain of head!)
 ********************************************************************/
void listappend(struct node *head, struct node *tail) {
  if (head->next == NULL)
    head->next = tail;
  else listappend(head->next, tail);
}

/*********************************************************************
 * Same as listappend, but makes a copy of tail to avoid affecting the
 * original.
 *********************************************************************/
void listappendcopy(struct node *head, const struct node *tail) {
  listappend(head, listcopy(tail));
}

/*********************************************************************
 * Links insertant to head at index, the end of insertant links to the
 * remainder of head.  Be very careful not to link your lists in a
 * circle (use listinsertcopy if you do not want to affect the list
 * you are inserting here).  Do not insert out of bounds (BAD)!
 *********************************************************************/
void listinsert(struct node *head, int index, struct node *insertant) {
  if (index == 0)
    // insertant is the head here (index 0).
    // Append the rest of the original head.
    listappend(insertant, head);
  else
    // recurse to next element
    listinsert(head->next, index-1, insertant);

  // fix link on the way out
  if (index == 1)
    // insertant starts at index 1 from this head.  It should be linked next.
    head->next = insertant;
}

/************************************************************
 * same as listinsert, but makes a copy of insertant to avoid
 * affecting the original list.
 ************************************************************/
void listinsertcopy(struct node *head, int index, const struct node *insertant) {
  listinsert(head, index, listcopy(insertant));
}

/*********************************************************************
 * determine the size of a list.  Very important as you do not want to
 * go out of bounds!
 *********************************************************************/
size_t listsize(const struct node *head) {
  if (head == NULL)
    return (size_t)0;
  return (size_t)(listsize(head->next)+1);
}

/****************************************************************
 * Get data value of given list at given index.  Do not go out of
 * bounds! (bad things will happen.)
 ****************************************************************/
int listgetdata(const struct node *head, int index) {
  if (index == 0) // Reached index
    return head->data;
  return (listgetdata(head->next, index-1));
}

// Decided against saving the caller from being stupid
/*
int listsetdata(struct node *head, int index, int ndata) {
  if (head == NULL) // Got all the way to the end without exausting index!
    return 1;       // throw an error code (no data set)

  if (index == 0) { // Finally
    head->data = ndata; // set value
    return 0; // return success
  }
  // Go deeper (and propogate error code back up to caller)
  return listsetdata(head->next, index-1, ndata);
}
*/

/***************************************************************
 * Set the data value of the index of a given list to a new data
 * value.  Do not go out of bounds! (bad things will happen.)
 ***************************************************************/
void listsetdata(struct node *head, int index, int ndata) {
  if (index == 0) // This is it
    head->data = ndata; // set value
  // go deeper on a sub list
  else listsetdata(head->next, index-1, ndata);
}

/********************************************************************
 * Delete element at index.  Returns pointer to the head.  You will
 * need this if you want to delete the zeroeth element in the list as
 * the old list pointer will point to a nonexistant head
 ********************************************************************/
struct node *listdelelem(struct node *head, int index) {
  if (index == 0) {
    struct node *old = head;
    head = head->next;
    free(old);
    return head;
  }
  head->next = listdelelem(head->next, index-1);
  return head;
}
  
