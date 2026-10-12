#include "apc.h"

newList sub(char *n1, char *n2){

  newList num1 = createList(n1); /* List of n1 */
  newList num2 = createList(n2); /* List of n2 */
  newList res = createList(NULL); /* Empty list to store the result */

  dnode dummy; /* Dummy node to make it easier */
  dummy.next = NULL;
  dummy.prev = NULL;
  dnode *curr = &dummy; /* Curr node to track */

  /* Start the operation from the both the tails */
  dnode *t1 = num1.tail;
  dnode *t2 = num2.tail;

  int diff = 0, borrow = 0;

  while(t1 || t2){

    diff = borrow; /* Borrow to start with */

    /* Calculate the difference */
    if(t1) diff += t1->data;
    if(t2) diff -= t2->data;

    /* If the difference is negative borrow from the previous value */
    if(diff < 0){
      diff += 10;
      borrow = -1; /* Took borrow */
    }
    else borrow = 0;

    /* Result list construction */
    dnode *newnode = malloc(sizeof(dnode));
    newnode->data = diff;
    newnode->next = NULL;
    newnode->prev = curr;
    if(curr == &dummy) newnode->prev = NULL;
    curr->next = newnode;
    curr = curr->next;

    /* Move both the pointers */
    if(t1) t1 = t1->prev;
    if(t2) t2 = t2->prev;

  }

  res.head = dummy.next;

  /* Trim down the Leading zeros, which doesn't make much sense */
  dnode *temp = curr;
  while(temp->data == 0){
    temp = temp->prev;
  }

  res.tail = temp;

  return res;

}
