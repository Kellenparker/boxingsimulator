#include "Roster.h"
#include "Fighter.h"
#include "RNG.h"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

std::vector<std::vector<Fighter>> Fighters;
std::vector<Fighter> Retired;

Fighter* fightList[450][2];
int fightWait[450];
int fightAmount = 0;

static const std::string weightClasses[] = { "flyweight", "bantamweight", "featherweight", "lightweight" , "welterweight", "middleweight" , "lightheavyweight", "cruiserweight" , "heavyweight" };

static const int classWeights[] = { 112, 118, 126, 135, 147, 160, 175, 200, 220 };

const int size = 9;

int retirements[9];

static const int NUMFIGHTERS = 100;

Roster::Roster()
{
	Fighters.resize(size);
	for (int i = 0; i < size; i++)
		Fighters[i].resize(NUMFIGHTERS);

	
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < NUMFIGHTERS; j++) {
			Fighters[i][j].CreateFighter(GetOverall(), classWeights[i]);
		}
	}

	//sort created Fighters
	for (int i = 0; i < size; i++)
	{
		std::sort(Fighters[i].begin(), Fighters[i].end(), std::greater<Fighter>());
	}
}

int Roster::GetOverall()
{
	float randNum = rng::randd(0.0, 1.0, false);

	if (randNum < .001)
		return rng::randd(90.0, 100.0, false);
	else if (randNum < .01)
		return rng::randd(80.0, 90.0, false);
	else if (randNum < .05)
		return rng::randd(70.0, 80.0, false);
	else if (randNum < .25)
		return rng::randd(60.0, 70.0, false);
	else if (randNum < .55)
		return rng::randd(50.0, 60.0, false);
	else
		return rng::randd(0.0, 40.0, false);

}

void Roster::Progress()
{

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < NUMFIGHTERS; j++) {
			Fighters[i][j].Progress();
		}
		std::sort(Fighters[i].begin(), Fighters[i].end(), std::greater<Fighter>());
	}
}

void Roster::IncrementAge()
{

	for (int i = 0; i < size; i++)
		for (int j = 0; j < NUMFIGHTERS; j++)
			if (Fighters[i][j].IncrementFighterAge()) {
				std::cout << "RETIREMENT-----------------------------------" << std::endl;
				Fighters[i][j].vPrint();
				std::cout << "---------------------------------------------" << std::endl;
				retirements[i]++;
				Retired.push_back(Fighters[i][j]);
				Fighters[i][j].NewFighter(classWeights[i]);
				std::cout << "NEW FIGHER-----------------------------------" << std::endl;
				Fighters[i][j].vPrint();
				std::cout << "---------------------------------------------" << std::endl;
			}

}

void Roster::PrintWeightClass(int w)
{

	for (int i = 0; i < NUMFIGHTERS; i++) {
		Fighters[w][i].vPrint();
	}

}

void Roster::FightFinder()
{

	for (int i = 0; i < (NUMFIGHTERS * size) / 2; i++) {

		

	}

}

Roster::~Roster()
{

}