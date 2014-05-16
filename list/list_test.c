#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void) {
  struct node *myList = listnew(6), *otherList = listnew(3);
  int i;
  int size;

  /* // DEBUGGING
  printf("Building lists...\n");
  printf("my list..."); */
  // add data for my list
  size = listsize(myList);
  for (i=0; i<size; i++)
    listsetdata(myList, i, 3*i);
  /*  // DEBUGGING
  printf("done\n");
  printf("other list..."); */
  // add data for other list
  size = listsize(otherList);
  for (i=0; i<size; i++)
    listsetdata(otherList, i, 2*i);
  /*
  printf("done\n"); */

  // print data for each list
  printf("Data in my list:\n");
  size = listsize(myList);
  for (i=0; i<size; i++)
    printf("%d\n", listgetdata(myList, i));
  printf("Data in other list:\n");
  size = listsize(otherList);
  for (i=0; i<size; i++)
    printf("%d\n", listgetdata(otherList, i));

  // combine list and print results
  printf("Appending copy of other list to my list:\n");
  listappendcopy(myList, otherList);
  printf("Data in my list:\n");
  size = listsize(myList);
  for (i=0; i<size; i++)
    printf("%d\n", listgetdata(myList, i));
  printf("Inserting other list at index 3 in my list:\n");
  listinsert(myList, 3, otherList);
  printf("Data in my list:\n");
  size = listsize(myList);
  for (i=0; i<size; i++)
    printf("%d\n", listgetdata(myList, i));

  // Cleanup
  listfree(myList); 
  myList = otherList = NULL;

  return 0;
}
