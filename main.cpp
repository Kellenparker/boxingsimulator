#include <stdlib.h>
#include <iostream>
#include "main.h"
#include "WeightClass.h"
#include "Roster.h"
#include "RNG.h"

static int YEAR;
static int MONTH;
static int ELAPSEDTIME;

int main()
{

	YEAR = 2019;
	MONTH = 1;
	ELAPSEDTIME = 0;

	WeightClass featherWeight(145);

	//game loop
	while (true)
	{
		for (MONTH = 1; MONTH <= 12; MONTH++)
		{
			std::cout << getMonth(MONTH) << " " << YEAR << std::endl;

			featherWeight.IncrementAge();
			//featherWeight.ProgressClass();
		}
		YEAR++;
		std::cin.get();
	}

}

const char* getMonth(int m)
{
	static const char* monthNames[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

	return monthNames[m - 1];
}
