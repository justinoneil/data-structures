#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/***************************************************************
 * Allocate a new list with n elements and initialize data to 0.
 ***************************************************************/
struct node *listnew(size_t n) {
  if (n <= 0)
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
  if (head == NULL) ; // Nothing to free
  else {
    listfree(head->next);
    free(head);
  }
}

/********************************************************************
 * Link tail to the end of head (be careful about using tail from now
 * on, it is part of the chain of head!).  Returns head pointer.  If
 * head is null, returns tail pointer.
 ********************************************************************/
struct node *listappend(struct node *head, struct node *tail) {
  if (head == NULL) head = tail; // return tail if head is null
  else if (head->next == NULL) head->next = tail;
  else listappend(head->next, tail);
  return head;
}

/*********************************************************************
 * Same as listappend, but makes a copy of tail to avoid affecting the
 * original.  Returns head pointer.  If head is null, this is a
 * pointer to the copy of tail.
 *********************************************************************/
struct node *listappendcopy(struct node *head, const struct node *tail) {
  return listappend(head, listcopy(tail));
}

/*********************************************************************
 * Links insertant to head at index, the end of insertant links to the
 * remainder of head.  Be careful not to link your lists in a circle
 * (use listinsertcopy if you do not want to affect the list you are
 * inserting here).  Returns pointer to head.  This is useful for
 * cases when you are inserting at the beginning of a list.  Otherwise
 * return value may be safely discarded.
 *********************************************************************/
struct node *listinsert(struct node *head, int index, struct node *insertant) {
  // negative index or null insertant
  if (index < 0 || !insertant) ;  // negative index or null insertant
  // insert at the beginning of the list
  else if (index == 0) { 
    listappend(insertant, head);
    head = insertant;
  }
  // insert at next element
  else if (index == 1) { 
    listappend(insertant, head->next);
    head->next = insertant;
  }
  // recurse on sub list
  else if (head) 
    listinsert(head->next, index-1, insertant);
  // relavent for inserting at the beginning.
  return head;
}

/************************************************************
 * same as listinsert, but makes a copy of insertant to avoid
 * affecting the original list.
 ************************************************************/
struct node *listinsertcopy(struct node *head, int index, const struct node *insertant) {
  // don't make a copy if index is out of bounds anyway.
  // Allow an empty head if the caller specified the index as 0
  if (listgetnode(head, index) || index == 0)
    head = listinsert(head, index, listcopy(insertant));
  return head;
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

/******************************************************************
 * Get a pointer to the node at index in the list starting at head.
 ******************************************************************/
struct node *listgetnode(struct node *head, int index) {
  if (head == NULL || index < 0) return NULL;
  else if (index == 0) return head;
  return listgetnode(head->next, index-1);
}

/*****************************************************************
 * Get data value of given list at given index.  Return garbage if
 * index out of range
 *****************************************************************/
int listgetdata(const struct node *head, int index) {
  struct node *elem = listgetnode(head, index);
  if (elem) return elem->data;
  return; // caller asked for an element out of bounds, will get garbage.
}

/***************************************************************
 * Set the data value of the index of a given list to a new data
 * value.  Does nothing if out of bounds.
 ***************************************************************/
void listsetdata(struct node *head, int index, int data) {
  struct node *elem = listgetnode(head, index);
  if (elem) elem->data = data;
}

/********************************************************************
 * Delete element at index.  Returns pointer to the head.  You will
 * need this if you want to delete the zeroeth element in the list as
 * the old list pointer will point to a nonexistant head.
 ********************************************************************/
struct node *listdelelem(struct node *head, int index) {
  if (index < 0 || !head) ; // index out of range or null head
  else if (index == 0) {    // this is the element to delete
    struct node *old = head;
    head = head->next;
    free(old);
  }
  else // recurse
    head->next = listdelelem(head->next, index-1);
  return head;
}
