#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "DataList.h"
#include "PartB.h"

#include "PartBGlobals.c"
 
void busDestructor(linkNode *node) {
	bus *data = (bus *)node->data;
	free(data->registNumber);
	list_nodeDestructor(node);
}

//TODO: Add bus types.
char *typeString(enum busType type) {
	switch (type) {
	case bus_MINI:
		return "Mini";
	case bus_REGULAR:
		return "Regular";
	case bus_DOUBLE:
		return "Double-Decker";
	default:
		return "Unknown Type";
	}
}

_Bool checkBusRegistration(void *param, void *data) {
	char *registNum = param;
	bus *theBus = data;

	return strcmp(registNum, theBus->registNumber) == 0;
}

//TODO: Add verification for bus numbers.
_Bool verifyRegistNumber(char* string) {
	char s[10], d[5], c;
	int matched = sscanf_s(string, "%9[a-zA-Z]%4[0-9]%c", s, 10, d, 5, &c);
	return matched == 2 || matched == 3;
}

void printBus(bus *theBus) {
	if (theBus == NULL)
		return;
	printf("Bus Registration Number: %s\n", theBus->registNumber);
	printf("Bus Type: %s\n", typeString(theBus->type));
	printf("Bus Capacity: %d\n", theBus->capacity);
}

void printBusNode(linkNode *node) {
	if (node == NULL)
		return;
	printBus(node->data);
	printf("\n");
}