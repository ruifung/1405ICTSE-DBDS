#pragma once
#define list_empty {NULL, NULL, 0}

typedef struct linkNode linkNode;

typedef _Bool(*listMatcher)(void *searchParam, void* data);
typedef void(*listNodeConsumer)(struct linkNode *node);
struct linkNode{
	void *data;
	struct linkNode *prev;
	struct linkNode *next;
	listNodeConsumer destructor;
};
typedef struct {
	linkNode *topNode;
	linkNode *lastNode;
	unsigned int length;
} linkList;

void list_nodeDestructor(linkNode *node);

void list_insertTop(linkList *list, void *data, listNodeConsumer destructor);
void list_insertEnd(linkList *list, void *data, listNodeConsumer destructor);
void list_iterate(linkList *list, listNodeConsumer action);
void list_iterateReverse(linkList *list, listNodeConsumer action);

linkNode *list_search(linkList *list, void *searchParam, listMatcher cmpr);
_Bool list_searchAndDestroy(linkList *list, void *searchParam, listMatcher cmpr);
_Bool list_remove(linkNode *node);
