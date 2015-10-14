#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "DataList.h"
#include "PartB.h"

void busDestructor(linkNode *node) {
	bus *data = (bus *)node->data;
	free(data->registNumber);
	list_nodeDestructor(node);
}

char *typeString(int type) {

	return "";
}

_Bool checkBusRegistration(void *param, void *data) {
	char *registNum = param;
	bus *theBus = data;

	return strcmp(registNum, theBus->registNumber) == 0;
}

_Bool verifyRegistNumber(char* string) {

	return true;
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