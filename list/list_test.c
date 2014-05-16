#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*********************************************************************
 * Print each element of the list separated by a space and ending with
 * a newline.
 *********************************************************************/
void print_list(struct node *list) {
  if (list == NULL)
    printf("\n");
  else {
    printf("%d ", list->data);
    print_list(list->next);
  }
}

/*****************************************
 * Set data in the list to multiples of n.
 *****************************************/
void multiples(struct node *list, int n) {
  int length = listsize(list);
  int i;
  for (i = 0; i < length; i++)
    listsetdata(list, i, n*i);
}

int main(void) {
  struct node *myList = listnew(6), *otherList = listnew(3), 
    *copyList;
  
  multiples(myList, 3);
  multiples(otherList, 2);

  // print data for each list
  printf("Data in my list:\n");
  print_list(myList);
  printf("Data in other list:\n");
  print_list(otherList);

  // combine list and print results
  printf("Appending copy of other list to my list:\n");
  listappendcopy(myList, otherList);
  printf("Data in my list:\n");
  print_list(myList);

  printf("Inserting other list at index 3 in my list:\n");
  listinsert(myList, 3, otherList); // otherList is part of myList now.
  printf("Data in my list:\n");
  print_list(myList);

  // Try deleting individual elements
  printf("Deleting element 2 of my list\n");
  listdelelem(myList, 2);
  print_list(myList);
  
  printf("Deleting element 0 of my list\n");
  myList = listdelelem(myList, 0);
  print_list(myList);

  printf("Copying my list.\n");
  copyList = listcopy(myList);
  printf("Deleting my list.\n");
  listfree(myList);
  myList = otherList = NULL;
  printf("Contents of copy list:\n");
  print_list(copyList);

  listfree(copyList);
  copyList = NULL;

  return 0;
}
