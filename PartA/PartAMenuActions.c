#pragma once

#include "sc2.h"
#include "PartAUtil.c"

customer *promptCustomerInput();


#pragma region menu_MAIN
int actionAddToTop(unsigned int menuIndex) {
	list_insertTop(&custList, (void *)promptCustomerInput());
	return 0;
}

int actionAddAtEnd(unsigned int menuIndex) {
	list_insertEnd(&custList, (void *)promptCustomerInput());
	return 0;
}

int actionPrintFromHead(unsigned int menuIndex) {
	list_iterate(&custList, &printCustomer);
	printf("Press any key to continue.");
	sc2_getkey(true);
	return 0;
}

int actionPrintFromTail(unsigned int menuIndex) {
	list_iterateReverse(&custList, &printCustomer);
	printf("Press any key to continue.");
	sc2_getkey(true);
	return 0;
}

int actionDelete(unsigned int menuIndex) {
	menuMode = menu_DEL;
	return 1;
}

int actionExit(unsigned int menuIndex) {
	exit(0);
}
#pragma endregion

#pragma region menu_DEL
int delCustByID(unsigned int index) {
	unsigned int id;
	bool hasValue = false;
	char count = 0;
	while (true) {
		sc2_clrscr();
		printf("Delete Customer\n");
		printf("---------------\n");
		printf("Customer ID:");
		hasValue = sc2_getint(&id);
		if (hasValue || count == 3)
			break;
		count++;
	}
	matcherParam param = { match_ID, &id };
	list_searchAndDestroy(&custList, &param, &matchCustomer);
	menuMode = menu_MAIN;
	return 1;
}

int delCustByName(unsigned int index) {
	char *name = NULL;
	char count = 0;
	while (true) {
		sc2_clrscr();
		printf("Delete Customer\n");
		printf("---------------\n");
		printf("Customer Name:");
		sc2_store();
		name = malloc(sc2_getNextLen());
		sc2_getStore(name, sc2_getNextLen());
	}
	matcherParam param = { match_NAME, &name };
	list_searchAndDestroy(&custList, &param, &matchCustomer);
	free(name);
	menuMode = menu_MAIN;
	return 1;
}

int delCustByPartialName(unsigned int index) {
	char *name = NULL;
	char count = 0;
	while (true) {
		sc2_clrscr();
		printf("Delete Customer\n");
		printf("---------------\n");
		printf("Partial Customer Name:");
		sc2_store();
		name = malloc(sc2_getNextLen());
		sc2_getStore(name, sc2_getNextLen());
	}
	matcherParam param = { match_PARTIALNAME, &name };
	while (list_searchAndDestroy(&custList, &param, &matchCustomer)) {};
	free(name);
	menuMode = menu_MAIN;
	return 1;
}
#pragma endregion
