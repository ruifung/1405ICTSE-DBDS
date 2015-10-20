#pragma once

typedef struct {
	char *registNumber;
	int type;
	unsigned int capacity;
} bus;

enum menuMode {
	menu_MAIN
};

enum busType {
	bus_MINI,
	bus_REGULAR,
	bus_DOUBLE,
	bus_PLACEHOLDERLAST
};