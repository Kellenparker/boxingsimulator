#include "WeightClass.h"
#include "Fighter.h"
#include "RNG.h"
#include <vector>
#include <iostream>

std::vector<Fighter> cFlyweight;
std::vector<Fighter> cBantamweight; 
std::vector<Fighter> cFeatherweight;
std::vector<Fighter> cLightweight;
std::vector<Fighter> cWelterweight;
std::vector<Fighter> cMiddleweight;
std::vector<Fighter> cLightheavyweight;
std::vector<Fighter> cCruiserweight;
std::vector<Fighter> cHeavyweight;

WeightClass::WeightClass()
{
	
}

void WeightClass::CreateFighters(int w)
{

	cFlyweight.resize(NUMFIGHTERS);
	cBantamweight.resize(NUMFIGHTERS);
	cFeatherweight.resize(NUMFIGHTERS);
	cLightweight.resize(NUMFIGHTERS);
	cWelterweight.resize(NUMFIGHTERS);
	cMiddleweight.resize(NUMFIGHTERS);
	cLightheavyweight.resize(NUMFIGHTERS);
	cCruiserweight.resize(NUMFIGHTERS);
	cHeavyweight.resize(NUMFIGHTERS);

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

		switch (w) {
		case 112: cFlyweight[i].CreateFighter(overall, w);
			break;
		case 118: cBantamweight[i].CreateFighter(overall, w);
			break;
		case 126: cFeatherweight[i].CreateFighter(overall, w);
			break;
		case 135: cLightweight[i].CreateFighter(overall, w);
			break;
		case 147: cWelterweight[i].CreateFighter(overall, w);
			break;
		case 160: cMiddleweight[i].CreateFighter(overall, w);
			break;
		case 175: cLightheavyweight[i].CreateFighter(overall, w);
			break;
		case 200: cCruiserweight[i].CreateFighter(overall, w);
			break;
		case 220: cHeavyweight[i].CreateFighter(overall, w);
			break;
		}
	}

}

void WeightClass::ProgressClass()
{
	for (int i = 0; i < NUMFIGHTERS; i++)
	{
		cFlyweight[i].Progress();
		cBantamweight[i].Progress();
		cFeatherweight[i].Progress();
		cLightweight[i].Progress();
		cWelterweight[i].Progress();
		cMiddleweight[i].Progress();
		cLightheavyweight[i].Progress();
		cCruiserweight[i].Progress();
		cHeavyweight[i].Progress();
	}
}

void WeightClass::IncrementAge()
{
	for (int i = 0; i < NUMFIGHTERS; i++)
	{
		cFlyweight[i].IncrementFighterAge();
		cBantamweight[i].IncrementFighterAge();
		cFeatherweight[i].IncrementFighterAge();
		cLightweight[i].IncrementFighterAge();
		cWelterweight[i].IncrementFighterAge();
		cMiddleweight[i].IncrementFighterAge();
		cLightheavyweight[i].IncrementFighterAge();
		cCruiserweight[i].IncrementFighterAge();
		cHeavyweight[i].IncrementFighterAge();
	}
}

void WeightClass::PrintFighters(int w)
{
	switch (w) {
	case 112:
		for (int i = 0; i < NUMFIGHTERS; i++)
			cFlyweight[i].vPrint();
		break;
	case 118:
		for (int i = 0; i < NUMFIGHTERS; i++)
			cBantamweight[i].vPrint();
		break;
	case 126:
		for (int i = 0; i < NUMFIGHTERS; i++)
			cFeatherweight[i].vPrint();
		break;
	case 135: 
		for (int i = 0; i < NUMFIGHTERS; i++)
			cLightweight[i].vPrint();
		break;
	case 147: 
		for (int i = 0; i < NUMFIGHTERS; i++)
			cWelterweight[i].vPrint();
		break;
	case 160: 
		for (int i = 0; i < NUMFIGHTERS; i++)
			cMiddleweight[i].vPrint();
		break;
	case 175:
		for (int i = 0; i < NUMFIGHTERS; i++)
			cLightheavyweight[i].vPrint();
		break;
	case 200:
		for (int i = 0; i < NUMFIGHTERS; i++)
			cCruiserweight[i].vPrint();
		break;
	case 220:
		for (int i = 0; i < NUMFIGHTERS; i++)
			cHeavyweight[i].vPrint();
		break;
	}
}

WeightClass::~WeightClass()
{

}
