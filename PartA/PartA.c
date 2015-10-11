#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include "PartA.h"
#include "DataList.h"
#include "sc2.h"

#pragma region privdeclarations
enum matchMode {
	match_ID,
	match_NAME,
	match_ADDR,
	match_ORDERDESC
};

enum menuMode {
	menu_MAIN,
	menu_MODIFY,
	menu_DEL
};
typedef struct matcherParam {
	enum matchMode mode;
	void *param;
} matcherParam;
#pragma endregion

#pragma region global vars
linkList custList = list_empty;
unsigned int itemCount = 0;
enum menuMode menuMode = menu_MAIN;
#pragma endregion

#pragma region utility functions
void destructCustomer(linkNode *node) {
	customer *cust = (customer *)node->data;
	free(cust->name);
	free(cust->gender);
	free(cust->orderDesc);
	free(cust->addr);
	list_nodeDestructor(node);
}

bool matchCustomer(void *param, void *data) {
	matcherParam *matchParam = (matcherParam *)param;
	customer *cust = (customer *)data;
	switch (matchParam->mode) {
	case match_ID:
		break;
	case match_NAME:
		break;
	case match_ADDR:
		break;
	case match_ORDERDESC:
		break;
	}
	return false;
}
#pragma endregion

customer *promptCustomerInput() {
	customer *cust = malloc(sizeof(customer));

	printf("Entering New Customer\n");
	printf("---------------------\n");

	while (true) {
		printf("ID: ");
		if (sc2_getint(&cust->id))
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

int actionAddToTop(unsigned int menuIndex) {
	list_insertTop(&custList, (void *)promptCustomerInput(), &destructCustomer);
}

int actionAddAtEnd(unsigned int menuIndex) {
	list_insertEnd(&custList, (void *)promptCustomerInput(), &destructCustomer);
}

void printCustomer(linkNode *node) {
	customer *cust = (customer*)(node->data);
	printf("Name: %s\n, ID: %u\n, Addr: %s\n",
		cust->name, cust->id, cust->addr);
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

int keyHandler(sc2_key key) {
	// Esc key
	if (sc2_keycmp(key, (sc2_key) {.modifiers.value = 0, 27 })) {

	}
	else if (sc2_keycmp(key, (sc2_key) {.modifiers.bits = {0, 0, 1}, 67 })) {

	}
}

_Bool custCmprByName(void *cmpTo, void *data) {
	customer *cust1 = (customer *)cmpTo;
	customer *cust2 = (customer *)data;
	return strcmp(cust1->name, cust2->name) == 0;
}

void showView() {
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
		sc2m_add("Delete by ID", "Delete customer with ID", NULL);
		sc2m_add("Delete by Name (Exact)", "Delete all customers with matching name.", NULL);
		sc2m_add("Delete by Name (Partial)", "Delete all customers with partially matching name", NULL);
		break;
	}
}

int main(int argc, char **argv) {
	while (1) {
		showView();
	}
}