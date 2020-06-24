/*
#include "WeightClass.h"
#include "Fighter.h"
#include "RNG.h"
#include <vector>
#include <iostream>

WeightClass::WeightClass()
{
	
}

void WeightClass::CreateFighters(int w)
{

	


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
*/