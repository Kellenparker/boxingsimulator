#pragma once

#include <stdlib.h>
#include <iostream>
#include "Roster.h"
#include "RNG.h"

int main();

void mainMenu(int m, int y, int* s, Roster r);

const char* getMonth(int m);