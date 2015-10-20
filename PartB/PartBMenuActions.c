#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "sc2.h"
#include "DataList.h"

#include "PartBGlobals.c"
#include "PartBUtil.c"

int actionArriving(int index) {
	if (busQueue.maxLength > 0 && busQueue.length + 1 > busQueue.maxLength) {
		printf("\nBus Queue is Full!\nLimit is %d\n", busQueue.maxLength + 1);
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
		sc2_getStore(theBus->registNumber, sc2_getNextLen());

		for (int i = 0; i < strlen(theBus->registNumber); i++)
			theBus->registNumber[i] = toupper(theBus->registNumber[i]);

		if (verifyRegistNumber(theBus->registNumber))
			break;
		else {
			printf("Invalid Registration Number!\n");
			free(theBus->registNumber);
			theBus->registNumber = NULL;
		}
	}

	while (true) {
		printf("Valid Bus Types:\n");
		for (int i = 0; i < bus_PLACEHOLDERLAST; i++) {
			printf("%d: %s\n", i, typeString(i));
		}
		printf("Bus Type:");

		if (sc2_getint(&theBus->type) && 
				theBus->type >= 0 && theBus->type < bus_PLACEHOLDERLAST)
			break;
		else
			printf("Invalid bus type!\n");
	}
	
	while (true) {
		printf("Bus Capacity:");

		if (sc2_getint(&theBus->capacity) && theBus->capacity > 0)
			break;
		else
			printf("Invalid capacity!");
	}
	printf("\nBus Details:\n");
	printBus(theBus);
	printf("Commit bus to queue?");
	if (sc2_confirm(true))
		list_insertEnd(&busQueue, theBus);
	return 1;
}

int actionLeaving(int index) {
	if (busQueue.length > 0) {
		bus *theBus = busQueue.topNode->data;

		sc2_clrscr();
		printf("Bus Leaving\n");
		printf("-----------\n");
		printBus(theBus);

		list_remove(busQueue.topNode);
	}
	else
		printf("No busses in queue!\n");
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

	for (int i = 0; i < strlen(searchRegist); i++)
		searchRegist[i] = toupper(searchRegist[i]);

	linkNode *node = list_search(&busQueue, searchRegist, &checkBusRegistration);

	if (node == NULL || node->data == NULL) {
		printf("No bus with registration %s found!\n", searchRegist);
		printf("Press any key to continue.");
		sc2_getkey(true);
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
	sc2_getkey(true);
	return 0;
}

int actionCount(int index) {
	printf("\nNumber of busses in queue: %d\n", busQueue.length);
	printf("Press any key to continue.");
	sc2_getkey(true);
	return 0;
}

int actionExit(int index) {
	exit(0);
}