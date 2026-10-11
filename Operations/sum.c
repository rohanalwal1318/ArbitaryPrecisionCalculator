#include "apc.h"

newList sum(char *n1, char *n2){

  newList num1 = createList(n1);
  newList num2 = createList(n2);
  newList res = createList(NULL);

  dnode dummy;
  dummy.next = NULL;
  dummy.prev = NULL;
  dnode *curr = &dummy;

  dnode *t1 = num1.tail;
  dnode *t2 = num2.tail;

  int sum = 0, carry = 0;

  while(t1 || t2){
    
    sum = carry;
    if(t1) sum += t1->data;
    if(t2) sum += t2->data;

    dnode *newnode = malloc(sizeof(dnode));
    newnode->data = (sum % 10);
    newnode->next = NULL;
    newnode->prev = curr;
    if(curr == &dummy) newnode->prev = NULL;
    carry = (sum / 10);
    curr->next = newnode;
    curr = curr->next;

    if(t1) t1 = t1->prev;
    if(t2) t2 = t2->prev;

  }

  if(carry){
    dnode *newnode = malloc(sizeof(dnode));
    newnode->data = carry;
    newnode->next = NULL;
    newnode->prev = curr;
    curr->next = newnode;
    curr = curr->next;
  }

  res.head = dummy.next;
  res.tail = curr;

  return res;

}