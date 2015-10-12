#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "DataList.h"
#include "PartA.h"
#include "PartAGlobals.c"

_Bool custCmprByName(void *cmpTo, void *data) {
	customer *cust1 = (customer *)cmpTo;
	customer *cust2 = (customer *)data;
	return strcmp(cust1->name, cust2->name) == 0;
}

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
		return (*(unsigned int *)matchParam->param == cust->id);
	case match_NAME:
		return strcmp(matchParam->param, cust->name) == 0;
	case match_PARTIALNAME:
		return !!strstr(cust->name, matchParam->param);
	case match_ADDR:
		return strcmp(matchParam->param, cust->addr);
	case match_ORDERDESC:
		return strcmp(matchParam->param, cust->orderDesc);
	}
	return false;
}

void printCustomer(linkNode *node) {
	customer *cust = (customer*)(node->data);
	printf("Name: %s\n, ID: %u\n, Addr: %s\n",
		cust->name, cust->id, cust->addr);
}