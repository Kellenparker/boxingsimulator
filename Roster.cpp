#include "Roster.h"
#include "Fighter.h"
#include "Fight.h"
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

							std::cout << "Low-level prospect fight" << std::endl;

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

						std::cout << "Prospect fight" << std::endl;

						FightPrint(fightAmount);

						fightAmount++;

						break;

					}

				}

				break;

			}

			//Fighters with high success close to retirement will look for easier "money fights"
			if (Fighters[i][j].GetAttribute(6, false, 0) > 35 && Fighters[i][j].GetAttribute(9, false, 0) > 80 && !Fighters[i][j].GetHasFight()) {

				//Find fighter with high popularity and lower overall
				for (int k = 0; k > NUMFIGHTERS; k++) {

					float ovrDif = rng::randd(5.0, 10.0, false);

					//Popularity cutoff is 80; Overall difference must be >5
					//Fighter has a good chance of taking this fight as it will be very profitable (90%)
					if (Fighters[i][k].GetAttribute(3, false, 0) > 80 && (Fighters[i][j].overall - ovrDif) >= Fighters[i][k].overall && rng::randd(0.0, 1.0, false) < .90 && !Fighters[i][k].GetHasFight()) {

						Fighters[i][j].SetHasFight(true);
						Fighters[i][k].SetHasFight(true);

						fightList[fightAmount][0] = &Fighters[i][j];
						fightList[fightAmount][1] = &Fighters[i][k];

						//Big name fights like this will have a longer build up time than most
						fightWait[fightAmount] = rng::randd(3.0, 6.0, false);

						std::cout << "Late career money fight" << std::endl;

						FightPrint(fightAmount);

						fightAmount++;

						break;

					}

				}

				break;

			}

			//Top level fighters will attempt to find fights close in ovr(+-10)
			//They will also take fights more rarely than other fighters
			//*top level includes 70+ overall
			if (Fighters[i][j].overall > 60 && !Fighters[i][j].GetHasFight()) {

				for (int k = 0; k < NUMFIGHTERS; k++) {

					if (Fighters[i][j].isEqual(Fighters[i][k])) continue;

					//50% chance for fight to make
					if ((Fighters[i][j].overall - Fighters[i][k].overall < rng::randd(8.0, 12.0, false) || Fighters[i][k].overall - Fighters[i][j].overall < rng::randd(8.0, 12.0, false)) && !Fighters[i][k].GetHasFight() && rng::randd(0.0,1.0,false) > .5) {

						Fighters[i][j].SetHasFight(true);
						Fighters[i][k].SetHasFight(true);

						fightList[fightAmount][0] = &Fighters[i][j];
						fightList[fightAmount][1] = &Fighters[i][k];

						//Big name fights like this will have a longer build up time than most
						fightWait[fightAmount] = rng::randd(3.0, 6.0, false);

						std::cout << "Top Level Fight" << std::endl;

						FightPrint(fightAmount);

						fightAmount++;

						break;

					}

				}

				break;

			}

			//All other fighters will match up evenly and have a pretty short time to fight
			//and a high chance of acceptence
			if(!Fighters[i][j].GetHasFight()) {

				for (int k = 0; k < NUMFIGHTERS; k++) {

					if (Fighters[i][j].isEqual(Fighters[i][k])) continue;

					//50% chance for fight to make
					if ((Fighters[i][j].overall - Fighters[i][k].overall < rng::randd(8.0, 12.0, false) || Fighters[i][k].overall - Fighters[i][j].overall < rng::randd(8.0, 12.0, false)) && !Fighters[i][k].GetHasFight() && rng::randd(0.0, 1.0, false) < .7) {

						Fighters[i][j].SetHasFight(true);
						Fighters[i][k].SetHasFight(true);

						fightList[fightAmount][0] = &Fighters[i][j];
						fightList[fightAmount][1] = &Fighters[i][k];

						//Mid-low level fights will have quick camps
						fightWait[fightAmount] = rng::randd(1.0, 3.0, false);

						std::cout << "Mid-Low Level Fight" << std::endl;

						FightPrint(fightAmount);

						fightAmount++;

						break;

					}

				}

				break;

			}
			
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