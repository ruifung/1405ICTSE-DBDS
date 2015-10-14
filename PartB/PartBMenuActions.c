#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "sc2.h"
#include "DataList.h"

#include "PartBGlobals.c"
#include "PartBUtil.c"

int actionArriving(int index) {
	if (busQueue.maxLength > 0 && busQueue.length + 1 > busQueue.maxLength) {
		printf("\nBus Queue is Full!");
		printf("Press any key to continue.");
		sc2_getkey(true);
		return 0;
	}

	bus *theBus = malloc(sizeof(bus));

	sc2_clrscr();
	printf("New Bus Arriving\n");
	printf("----------------\n");
	while (true) {
		printf("Registration Number:");
		sc2_store();

		theBus->registNumber = malloc(sc2_getNextLen());
		sc2_getStore(theBus->registNumber, sc2_getNextLen);

		if (verifyRegistNumber(theBus->registNumber))
			break;
		else
			printf("Invalid Registration Number!");
	}

	printf("Bus Type:");
	sc2_getint(&theBus->type);
	printf("Bus Capacity:");
	sc2_getint(&theBus->capacity);

	printBus(theBus);
	printf("Commit bus to queue? (Y/N)");
	sc2_confirm(true);
	list_insertEnd(&busQueue, theBus);
	return 1;
}

int actionLeaving(int index) {
	bus *theBus = busQueue.topNode->data;

	sc2_clrscr();
	printf("Bus Leaving\n");
	printf("-----------\n");
	printBus(theBus);

	list_remove(busQueue.topNode, busQueue.nodeDestructor);

	printf("Press any key to continue.");
	sc2_getkey(true);
	return 0;
}

int actionSearch(int index) {
	char *searchRegist;

	sc2_clrscr();
	printf("Bus Queue Search\n");
	printf("----------------\n");
	printf("Registration Number:");
	sc2_store();
	
	searchRegist = malloc(sc2_getNextLen());
	sc2_getStore(searchRegist, sc2_getNextLen());

	linkNode *node = list_search(&busQueue, searchRegist, &checkBusRegistration);

	if (node == NULL || node->data == NULL) {
		printf("No bus with registration %s found!\n", searchRegist);
		return 0;
	}

	printf("Bus Found:\n");
	printBus(node->data);

	printf("Press any key to continue.");
	sc2_getkey(true);
	return 0;
}

int actionListAll(int index) {
	sc2_clrscr();
	printf("Listing details for all busses in queue.\n");
	printf("----------------------------------------\n");
	list_iterate(&busQueue, &printBusNode);
	printf("Press any key to continue.");
	sc2_getkey;
}

int actionCount(int index) {
	printf("\nNumber of busses in queue: %d", busQueue.length);
	printf("Press any key to continue.");
	sc2_getkey(true);
}

int actionExit(int index) {
	exit(0);
}