#include "WeightClass.h"
#include "Fighters.h"
#include <cmath>
#include <vector>
#include <iostream>

std::vector<Fighters> allFighters;

WeightClass::WeightClass(int w)
{
	allFighters.resize(NUMFIGHTERS);

	int fighterOverall = 100;
	for (int i = 0; i < NUMFIGHTERS; i++)
	{
		if (i == 0) fighterOverall = 100;
		else fighterOverall = (-25 * log10(i + 1.0)) + 100;
		allFighters[i].CreateFighter(fighterOverall, w);
		allFighters[i].PrintFighter();
	}
}

void WeightClass::ProgressClass()
{
	for (int i = 0; i < NUMFIGHTERS; i++)
	{
		allFighters[i].Progress();
		printf("------------------------------------\n");
		allFighters[i].PrintFighter();
	}
}

void WeightClass::IncrementAge()
{
	for (int i = 0; i < NUMFIGHTERS; i++)
	{
		allFighters[i].IncrementFighterAge();

		allFighters[i].PrintFighter();
	}
}

WeightClass::~WeightClass()
{

}
