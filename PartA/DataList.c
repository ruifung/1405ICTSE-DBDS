#include "DataList.h"
#include <stdlib.h>

linkNode *list_newNode() {
	linkNode *node = malloc(sizeof(linkNode));
	node->prev = NULL;
	node->next = NULL;
	node->data = NULL;
	return node;
}

void list_nodeDestructor(linkNode *node) {
	free(node->data);
}

void list_insertTop(linkList *list, void *data, listNodeConsumer destructor) {
	linkNode *node = list_newNode();

	if (list->length > 0 && list->topNode != NULL) {
		linkNode *oldNode = list->topNode;
		oldNode->prev = node;
		node->next = oldNode;
	}
	node->data = data;
	node->destructor = destructor == NULL ? &list_nodeDestructor : destructor;
	list->topNode = node;
	list->length++;
	if (list->length == 1 && list->lastNode == NULL)
		list->lastNode = list->topNode;
}

void list_insertEnd(linkList *list, void *data, listNodeConsumer destructor) {
	linkNode *node = list_newNode();
	if (list->length == 0) {
		list->topNode = node;
		list->lastNode = node;
	}
	else {
		node->prev = list->lastNode;
	}
	list->length++;
	node->data = data;
	node->destructor = destructor == NULL ? &list_nodeDestructor : destructor;
}

void list_iterate(linkList *list, listNodeConsumer action) {
	linkNode *currentNode = list->topNode;
	while (currentNode != NULL) {
		action(currentNode);
		currentNode = currentNode->next;
	}
}

void list_iterateReverse(linkList *list, listNodeConsumer action) {
	linkNode *currentNode = list->topNode;
	while (currentNode != NULL) {
		action(currentNode);
		currentNode = currentNode->prev;
	}
}

linkNode *list_search(linkList *list, void *searchParam, listMatcher cmpr) {
	linkNode *currentNode = list->topNode;
	while (currentNode != NULL) {
		if (cmpr(searchParam, currentNode->data)) {
			return currentNode;
		}
		currentNode = currentNode->next;
	}
	return NULL;
}

_Bool list_searchAndDestroy(linkList *list, void *searchParam, listMatcher cmpr) {
	linkNode *node = list_search(list, searchParam, cmpr);
	if (node == NULL)
		return 0;
	return list_remove(node);
}

_Bool list_remove(linkNode *node) {
	if (node == NULL)
		return 0;
	if (node->prev != NULL)
		node->prev->next = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	node->destructor(node);
	free(node);
	return 1;
}