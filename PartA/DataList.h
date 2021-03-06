#pragma once
#define list_new(destructor) {NULL, NULL, 0, 0, destructor}
#define list_empty list_new(&list_nodeDestructor)

typedef struct linkNode linkNode;
typedef struct linkList linkList;

typedef _Bool(*listMatcher)(void *searchParam, void* data);
typedef void(*listNodeConsumer)(struct linkNode *node);

struct linkNode {
	linkList *list;
	linkNode *prev;
	linkNode *next;
	void *data;
};
struct linkList {
	linkNode *topNode;
	linkNode *lastNode;
	unsigned int length;
	unsigned int maxLength;
	listNodeConsumer nodeDestructor;
};

void list_nodeDestructor(linkNode *node);

_Bool list_insertTop(linkList *list, void *data);
_Bool list_insertEnd(linkList *list, void *data);
void list_iterate(linkList *list, listNodeConsumer action);
void list_iterateReverse(linkList *list, listNodeConsumer action);

linkNode *list_search(linkList *list, void *searchParam, listMatcher cmpr);
_Bool list_searchAndDestroy(linkList *list, void *searchParam, listMatcher cmpr);
_Bool list_remove(linkNode *node);
