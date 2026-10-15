#include "apc.h"

newList mul(char *n1, char *n2)
{

  newList num1 = createList(n1);
  newList num2 = createList(n2);
  newList res = createList(NULL);

  int len1 = 0, len2 = 0;

  for (dnode *t = num1.head; t; t = t->next)
    len1++; /* List 1 Length */
  for (dnode *t = num2.head; t; t = t->next)
    len2++; /* List 2 Length */

  dnode dummy;
  dummy.next = NULL;
  dummy.prev = NULL;
  dnode *curr = &dummy;

  /* Initialize result all nodes with values 0, Length will be len1 + len2 */
  for (int i = 0; i < (len1 + len2); i++)
  {
    dnode *newnode = malloc(sizeof(dnode));
    newnode->data = 0;
    newnode->next = NULL;
    newnode->prev = curr;
    if (curr == &dummy)
      newnode->prev = NULL;
    curr->next = newnode;
    curr = curr->next;
  }

  res.head = dummy.next;
  res.tail = curr;

  dnode *shift = res.tail;
  int carry = 0;

  for (dnode *ptr2 = num2.tail; ptr2; ptr2 = ptr2->prev)
  {

    dnode *resptr = shift;
    dnode *ptr1 = num1.tail;

    while (ptr1 || carry > 0)
    {

      int val = (ptr1) ? ptr1->data : 0;

      int prod = (val * ptr2->data) + resptr->data + carry;

      resptr->data = prod % 10;

      carry = prod / 10;

      if (ptr1)
        ptr1 = ptr1->prev;

      resptr = resptr->prev;
    }

    shift = shift->prev;
  }

  // Optional: Trim leading zeros if necessary (except for a single "0")
  while (res.head && res.head->data == 0 && res.head != res.tail)
  {
    dnode *temp = res.head;
    res.head = res.head->next;
    res.head->prev = NULL;
    free(temp);
  }

  return res;
}
