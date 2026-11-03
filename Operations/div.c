#include "apc.h"

newList division(char *n1, char *n2){

  newList num1 = createList(n1);
  long long int num2 = atoll(n2);
  newList quo = createList(NULL);

  dnode *temp = num1.head;
  dnode dummy;
  dummy.next = dummy.prev = NULL;
  dnode *curr = &dummy;

  long long int value = 0;
  int printing = 0;
  
  while(temp){

    value = (value * 10) + temp->data;

    int q = (int)(value / num2);

    /* Construction of result list */
    if(q > 0 || printing || temp->next == NULL){
      dnode *newnode = malloc(sizeof(dnode));
      newnode->data = q;
      newnode->next = NULL;
      newnode->prev = curr; /* Updating previous */
      if(curr == &dummy) newnode->prev = NULL; /* Always First node should point to NULL */
      curr->next = newnode;
      curr = curr->next;
      printing = 1;
    }

    value = (value % num2);

    temp = temp->next;

  }

  quo.head = dummy.next;
  quo.tail = curr;
  
  return quo;

}