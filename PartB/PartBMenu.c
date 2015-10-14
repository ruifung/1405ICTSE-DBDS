#include <stdbool.h>
#include <stdlib.h>

#include "sc2.h"

#include "PartBMenuActions.c"

void startMenu() {
	while (true) {
		char *title;
		sc2m_reset();
		switch (menuMode) {
		case menu_MAIN:
			title = "Bus Queue Tracking System - DBDS PART B";
			sc2_title(title);
			sc2m_add("Bus Arriving", "Adds a bus to the queue.", &actionArriving);
			sc2m_add("Bus Leaving", "Dequeues a bus.", &actionLeaving);
			sc2m_add("Search for Bus", "Search for a bus in the queue.", &actionSearch);
			sc2m_add("List Busses", "Prints all busses in the queue.", &actionListAll);
			sc2m_add("Count Busses", "Counts the number of busses in the queue.", &actionCount);
			sc2m_add("Exit Program", NULL, &actionExit);
			sc2m_show(title);
			break;
		}
	}
}