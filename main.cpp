#include <stdlib.h>
#include <iostream>
#include "main.h"
#include "Roster.h"
#include "RNG.h"

static int YEAR;
static int MONTH;
static int ELAPSEDTIME;

static const std::string weightClasses[] = { "flyweight", "bantamweight", "featherweight", "lightweight" , "welterweight", "middleweight" , "lightheavyweight", "cruiserweight" , "heavyweight" };

static const int classWeights[] = { 112, 118, 126, 135, 147, 160, 175, 200, 220 };


int main()
{

	YEAR = 2019;
	MONTH = 1;
	ELAPSEDTIME = 0;

	int state = 0;

	Roster league;

	//game loop
	while (true)
	{
		for (MONTH = 1; MONTH <= 12; MONTH++)
		{
			mainMenu(MONTH, YEAR, &state, league);
			ELAPSEDTIME++;
			league.Progress();
			league.FightFinder();
		}
		YEAR++;
		league.IncrementAge();
	}

}

void mainMenu(int m, int y, int* s, Roster r)
{

	std::string raw;

	//state 0: main menu
	if(*s == 0) {
	
		//system("CLS");
		//std::cout << "" << std::flush;
		std::cout << getMonth(MONTH) << " " << YEAR << std::endl;
		std::cout << "\t1.Flyweight" << std::endl;
		std::cout << "\t2.Bantamweight" << std::endl;
		std::cout << "\t3.Featherweight" << std::endl;
		std::cout << "\t4.Lightweight" << std::endl;
		std::cout << "\t5.Welterweight" << std::endl;
		std::cout << "\t6.Middleweight" << std::endl;
		std::cout << "\t7.Light Heavyweight" << std::endl;
		std::cout << "\t8.Cruiserweight" << std::endl;
		std::cout << "\t9.Heavyweight" << std::endl;

		std::getline(std::cin, raw);
		if(raw != "") *s = std::stoi(raw);
	
	}

	if (*s != 0) {

		std::cout << getMonth(MONTH) << " " << YEAR << std::endl;
		r.PrintWeightClass(*s - 1);
		
		//Check if returning to main menu
		std::getline(std::cin, raw);
		if(raw != "")
			if (std::stoi(raw) == 1) *s = 0;

	}

}

const char* getMonth(int m)
{
	static const char* monthNames[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

	return monthNames[m - 1];
}
