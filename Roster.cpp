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

static const std::string weightClasses[] = { "flyweight", "bantamweight", "featherweight", "lightweight" , "welterweight", "middleweight" , "lightheavyweight", "cruiserweight" , "heavyweight" };

static const int classWeights[] = { 112, 118, 126, 135, 147, 160, 175, 200, 220 };

const int size = 9;

int retirements[9];

static const int NUMFIGHTERS = 10;

Fighter* fightList[(NUMFIGHTERS * size) / 2][2];
int fightWait[(NUMFIGHTERS * size) / 2];
int fightAmount = 0;

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

	for (int i = 0; i < NUMFIGHTERS; i++)
		Fighters[w][i].vPrint();

}

void Roster::FightFinder()
{

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < NUMFIGHTERS; j++) {
			
			//test if fighter already has fight scheduled and skip
			if (Fighters[i][j].GetHasFight()) continue;

			//if fighter is a prospect; find "can"
			if (Fighters[i][j].GetProspect()) {

				//if fighter overall isnt about 20; find any low level opponent
				if (Fighters[i][j].overall < 20) {

					for (int k = NUMFIGHTERS - 1; k >= 0; k--) {

						//test if fighter already has fight scheduled and skip
						if (Fighters[i][k].GetHasFight()) continue;

						//make sure fighter isnt a prospect and doesn't have a fight scheduled
						if (!Fighters[i][k].GetProspect() && !Fighters[i][k].GetHasFight()) {

							Fighters[i][j].SetHasFight(true);
							Fighters[i][k].SetHasFight(true);

							fightList[fightAmount][0] = &Fighters[i][j];
							fightList[fightAmount][1] = &Fighters[i][k];

							//Fight time for prospects seems to be lower than most
							//So fight time will be between 1-2 months
							fightWait[fightAmount] = rng::randd(1.0, 2.0, false);

							FightPrint(fightAmount);

							fightAmount++;

							break;

						}

					}

				}

				float ovrDif = rng::randd(8.0, 12.0, false);

				//Find fight for prospect will ~random overall difference
				for (int k = 0; k < NUMFIGHTERS; k++) {

					//Prospect will have 85% chance of taking fight
					if ((Fighters[i][j].overall > (Fighters[i][k].overall + ovrDif)) && !Fighters[i][k].GetHasFight() && rng::randd(0.0, 1.0, false) < .85) {

						Fighters[i][j].SetHasFight(true);
						Fighters[i][k].SetHasFight(true);

						fightList[fightAmount][0] = &Fighters[i][j];
						fightList[fightAmount][1] = &Fighters[i][k];

						//Fight time for prospects seems to be lower than most
						//So fight time will be between 1-2 months
						fightWait[fightAmount] = rng::randd(1.0, 2.0, false);

						FightPrint(fightAmount);

						fightAmount++;

						break;

					}

				}

			}

			//Non-prospects will attempt to find fights close in ovr(+-10)
			

		}

	}

}

void Roster::FightPrint(int index)
{

	std::cout << "Time Until Fight: " << fightWait[index] << " months." << std::endl;

	std::cout << "Fighter 1: ";
	fightList[index][0]->vPrint();

	std::cout << "Fighter 2: ";
	fightList[index][1]->vPrint();

	std::cout << "-------------------------------------------------" << std::endl;

}

Roster::~Roster()
{

}