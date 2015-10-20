#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "sc2.h"
#include "PartA.h"
#include "PartAGlobals.c"
#include "PartAMenuActions.c"

//TODO: Customer input verification
customer *promptCustomerInput() {
	customer *cust = malloc(sizeof(customer));

	printf("Entering New Customer\n");
	printf("---------------------\n");

	while (true) {
		matcherParam idSearch = { match_ID, &cust->id};
		printf("ID: ");
		if (sc2_getint(&cust->id) &&
				!list_search(&custList, &idSearch, &matchCustomer))
			break;
		sc2_beep();
	}

	printf("Name: ");
	sc2_store();

	printf("Gender: ");
	sc2_store();

	printf("Order Description: ");
	sc2_store();

	printf("Address: ");
	sc2_store();

	cust->nameLen = sc2_getNextLen();
	cust->name = malloc(cust->nameLen);
	sc2_getStore(cust->name, cust->nameLen);

	cust->genderLen = sc2_getNextLen();
	cust->gender = malloc(cust->genderLen);
	sc2_getStore(cust->gender, cust->genderLen);

	cust->orderDescLen = sc2_getNextLen();
	cust->orderDesc = malloc(cust->orderDescLen);
	sc2_getStore(cust->orderDesc, cust->orderDescLen);

	cust->addrLen = sc2_getNextLen();
	cust->addr = malloc(cust->addrLen);
	sc2_getStore(cust->addr, cust->addrLen);

	return cust;
}

int keyHandler(sc2_key key) {
	// Esc key
	if (sc2_keycmp(key, (sc2_key) { .modifiers.value = 0, 27 })) {

	}
	else if (sc2_keycmp(key, (sc2_key) { .modifiers.bits = { 0, 0, 1 }, 67 })) {

	}
	return 0;
}

void startMenu() {
	while (true) {
		sc2m_reset();
		switch (menuMode) {
		case menu_MAIN:
			sc2m_add("Add Customer to Top", NULL, &actionAddToTop);
			sc2m_add("Add Customer to End", NULL, &actionAddAtEnd);
			sc2m_add("Print all customers from top", NULL, &actionPrintFromHead);
			sc2m_add("Print all customers from tail", NULL, &actionPrintFromTail);
			sc2m_add("Remove a customer", NULL, &actionDelete);
			sc2m_add("Exit Program", NULL, &actionExit);
			sc2m_show("Customer Linked List PART A");
			break;
		case menu_MODIFY:
			break;
		case menu_DEL:
			sc2m_add("Delete by ID", "Delete customer with ID", &delCustByID);
			sc2m_add("Delete by Name (Exact)", "Delete all customers with matching name.", &delCustByName);
			sc2m_add("Delete by Name (Partial)", "Delete all customers with partially matching name", &delCustByPartialName);
			sc2m_show("Delete Customer");
			break;
		}
	}
}