#include "apc.h"

newList sub(char *n1, char *n2){

  newList num1 = createList(n1);
  newList num2 = createList(n2);
  newList res = createList(NULL);

  dnode dummy;
  dummy.next = NULL;
  dummy.prev = NULL;
  dnode *curr = &dummy;

  dnode *t1 = num1.tail;
  dnode *t2 = num2.tail;

  int diff = 0, borrow = 0;

  while(t1 || t2){

    diff = borrow;

    if(t1) diff += t1->data;
    if(t2) diff -= t2->data;

    if(diff < 0){
      diff += 10;
      borrow = -1;
    }
    else borrow = 0;

    dnode *newnode = malloc(sizeof(dnode));
    newnode->data = diff;
    newnode->next = NULL;
    newnode->prev = curr;
    if(curr == &dummy) newnode->prev = NULL;
    curr->next = newnode;
    curr = curr->next;

    if(t1) t1 = t1->prev;
    if(t2) t2 = t2->prev;

  }

  res.head = dummy.next;

  dnode *temp = curr;
  while(temp->data == 0){
    temp = temp->prev;
  }

  res.tail = temp;

  return res;

}
