#include "apc.h"

newList createList(char *num){

  if(num == NULL){
    newList ans = {NULL, NULL};
    return ans;
  }

  newList ans;

  dnode dummy;
  dummy.next = NULL;
  dummy.prev = NULL;
  dnode *curr = &dummy;

  while(*num){

    dnode *newnode = malloc(sizeof(dnode));
    newnode->data = (*num) - '0';
    newnode->next = NULL;
    newnode->prev = curr;
    if(curr == &dummy) newnode->prev = NULL;
    curr->next = newnode;
    curr = curr->next;
    num++;

  }

  ans.head = dummy.next;
  ans.tail = curr;

  return ans;

}

void printList(newList print){

  dnode *t = print.tail;

  while(t){
    printf("%d", t->data);
    t = t->prev;
  }

  puts("");

}

void freeList(newList f){

  dnode *t;

  while(f.head){
    t = f.head;
    f.head = (f.head)->next;
    free(t);
  }

}