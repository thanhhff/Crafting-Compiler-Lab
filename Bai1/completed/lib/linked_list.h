#ifndef LINK_LIST_DSLK1
#define LINK_LIST_DSLK1

typedef struct
{
	char *text;
	int *col;
	int count;
} elType;

typedef struct node
{
	elType data;
	struct node *next;
} node;

void insertFirst(node **head, elType data);
void insertLast(node **head, elType data);
void removeHead(node **head);
void removeTail(node **head);

// remove linked list
void removeNode(node **head);

// Count node
int lenNode(node *head);


#endif
