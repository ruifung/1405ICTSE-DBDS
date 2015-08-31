#pragma once
#ifndef LISTQUEUE
#define LISTQUEUE

typedef struct {
	void *data;
	node *prev;
	node *next;
} node;

typedef struct {
	node *head;
	node *tail;
	int length;
} list;

typedef struct {
	node *top;
	int depth;
} stack;

list listqueue_init();
stack stack_init();

void queue_push(list *list, void *data);
void *queue_pop(list *list);

void list_push(node *list, void *data);
void *list_get(node *list, int position);
int list_search(node *list, int startPos); //Add cmpr function ptr.
bool list_remove(node *list, int position);

void stack_push(stack *stack, void *data);
void *stack_pop(stack *stack);

#endif