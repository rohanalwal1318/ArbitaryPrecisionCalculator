#include "apc.h"

newList sum(char *n1, char *n2){

  newList num1 = createList(n1); /* List of n1 */
  newList num2 = createList(n2); /* List of n2 */
  newList res = createList(NULL); /* Empty List for storing the result */

  dnode dummy; /* Dummy node for simplicity */
  dummy.next = NULL;
  dummy.prev = NULL;
  dnode *curr = &dummy; /* curr pointer to track each node */

  dnode *t1 = num1.tail; /* start from tail */
  dnode *t2 = num2.tail; /* start from tail */

  int sum = 0, carry = 0;

  while(t1 || t2){
    
    sum = carry; /* Carry to start with */

    /* Add the digtis of the current place */
    if(t1) sum += t1->data;
    if(t2) sum += t2->data;

    /* Construction of result list */
    dnode *newnode = malloc(sizeof(dnode));
    newnode->data = (sum % 10);
    newnode->next = NULL;
    newnode->prev = curr; /* Updating previous */
    if(curr == &dummy) newnode->prev = NULL; /* Always First node should point to NULL */
    carry = (sum / 10);
    curr->next = newnode;
    curr = curr->next; /* Move the curr to the current node */

    /* Move both pointers accordingly */
    if(t1) t1 = t1->prev;
    if(t2) t2 = t2->prev;

  }

  /* If carry is still Left */
  if(carry){
    dnode *newnode = malloc(sizeof(dnode));
    newnode->data = carry;
    newnode->next = NULL;
    newnode->prev = curr;
    curr->next = newnode;
    curr = curr->next;
  }

  /* Update the result 'head' and 'tail' */
  res.head = dummy.next;
  res.tail = curr;

  return res; /* Return result List */

}