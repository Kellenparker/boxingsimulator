#include "WeightClass.h"
#include "Fighter.h"
#include "RNG.h"
#include <vector>
#include <iostream>

std::vector<Fighter> allFighters;

WeightClass::WeightClass()
{
	
}

void WeightClass::CreateFighters(int w)
{


	allFighters.resize(NUMFIGHTERS);

	float randNum;
	int overall;
	for (int i = 0; i < NUMFIGHTERS; i++)
	{
		randNum = rng::randd(0.0, 1.0, false);

		if (randNum < .001)
			overall = rng::randd(90.0, 100.0, false);
		else if (randNum < .01)
			overall = rng::randd(80.0, 90.0, false);
		else if (randNum < .05)
			overall = rng::randd(70.0, 80.0, false);
		else if (randNum < .25)
			overall = rng::randd(60.0, 70.0, false);
		else if (randNum < .55)
			overall = rng::randd(50.0, 60.0, false);
		else
			overall = rng::randd(0.0, 40.0, false);

		allFighters[i].CreateFighter(overall, w);
	}

}

void WeightClass::ProgressClass()
{

	for (int i = 0; i < NUMFIGHTERS; i++)
	{
		allFighters[i].Progress();
	}
}

void WeightClass::IncrementAge()
{
	for (int i = 0; i < NUMFIGHTERS; i++)
	{
		allFighters[i].IncrementFighterAge();
	}
}

void WeightClass::PrintFighters()
{
	for (int i = 0; i < NUMFIGHTERS; i++)
	{
		allFighters[i].vPrint();
	}
}

WeightClass::~WeightClass()
{

}
