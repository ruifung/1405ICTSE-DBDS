#pragma once

#include <stdlib.h>

#include "DataList.h"

#include "PartBUtil.c"

#define MAX_BUSSES 10;

enum menuMode {
	menu_MAIN
};

linkList busQueue = list_new(&busDestructor);
enum menuMode menuMode = menu_MAIN;