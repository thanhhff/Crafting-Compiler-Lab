#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

node *makeNode(elType data)
{
  node *p = (node *)malloc(sizeof(node));
  if (p == NULL)
    return NULL;
  p->data = data;
  p->next = NULL;
  return p;
}

void insertFirst(node **head, elType data)
{
  node *p = makeNode(data);
  if (*head == NULL)
    *head = p;
  else
  {
    p->next = *head;
    *head = p;
  }
}

void insertLast(node **head, elType data)
{
  node *p = makeNode(data);
  if (*head == NULL)
    *head = p;
  else
  {
    node *q = *head;
    while (q->next != NULL)
      q = q->next;
    q->next = p;
  }
}

void removeHead(node **head)
{
  if (*head == NULL)
    return;
  node *p = *head;
  *head = (*head)->next;
  p->next = NULL;

  if (p == *head)
    *head = NULL;
  free(p);
}

void removeTail(node **head)
{
  if (*head == NULL)
    return;
  node *p = *head;
  node *back;
  while (p->next != NULL)
  {
    back = p;
    p = p->next;
  }
  if (back != NULL)
    back->next = NULL;

  if (p == *head)
    *head = NULL;

  free(p);
}

void removeNode(node **head)
{
  node *p = NULL;
  while (*head != NULL)
  {
    p = *head;
    *head = (*head)->next;
    free(p);
  }
}

int lenNode(node *head)
{
  if (head == NULL)
    return 0;
  else
    return 1 + lenNode(head->next);
}
