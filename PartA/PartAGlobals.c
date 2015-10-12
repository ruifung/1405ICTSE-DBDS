#pragma once

#include <stdlib.h>

#include "DataList.h"

enum matchMode {
	match_ID,
	match_NAME,
	match_PARTIALNAME,
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

linkList custList = list_empty;
unsigned int itemCount = 0;
enum menuMode menuMode = menu_MAIN;