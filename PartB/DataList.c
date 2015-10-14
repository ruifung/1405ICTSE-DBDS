#include <stdbool.h>
#include <stdlib.h>

#include "DataList.h"

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

_Bool list_insertTop(linkList *list, void *data) {
	if (list->maxLength > 0 && list->length + 1 > list->maxLength)
		return false;

	linkNode *node = list_newNode();

	if (list->length > 0 && list->topNode != NULL) {
		linkNode *oldNode = list->topNode;
		oldNode->prev = node;
		node->next = oldNode;
	}
	node->data = data;
	list->topNode = node;
	list->length++;
	if (list->length == 1 && list->lastNode == NULL)
		list->lastNode = list->topNode;
	return true;
}

_Bool list_insertEnd(linkList *list, void *data) {
	if (list->maxLength > 0 && list->length + 1 > list->maxLength)
		return false;

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
	
	return true;
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

_Bool list_remove(linkNode *node, listNodeConsumer destructor) {
	if (node == NULL)
		return 0;
	if (node->prev != NULL)
		node->prev->next = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	destructor(node);
	free(node);
	return 1;
}

_Bool list_searchAndDestroy(linkList *list, void *searchParam, listMatcher cmpr) {
	linkNode *node = list_search(list, searchParam, cmpr);
	if (node == NULL)
		return 0;
	
	if (list->topNode == node)
		list->topNode = node->next;
	if (list->lastNode == node)
		list->lastNode = node->prev;
	list->length--;
	return list_remove(node, list->nodeDestructor);
}