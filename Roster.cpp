#include "Roster.h"

std::vector<std::vector<Fighter>> Fighters;
std::vector<Fighter> Retired;

static const std::string weightClasses[] = { "flyweight", "bantamweight", "featherweight", "lightweight" , "welterweight", "middleweight" , "lightheavyweight", "cruiserweight" , "heavyweight" };

static const int classWeights[] = { 112, 118, 126, 135, 147, 160, 175, 200, 220 };

const int size = 9;

int retirements[9];

static const int NUMFIGHTERS = 10;

std::vector<FightCard> FightCardVec;

Roster::Roster()
{
	Fighters.resize(size);
	for (int i = 0; i < size; i++)
		Fighters[i].resize(NUMFIGHTERS);

	FightCardVec.resize(10);
	Roster::current = 0;
	champs[9][2] = {};

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < NUMFIGHTERS; j++) {
			Fighters[i][j].CreateFighter(GetOverall(), classWeights[i], i);
		}
	}

	//sort created Fighters
	for (int i = 0; i < size; i++)
	{
		std::sort(Fighters[i].begin(), Fighters[i].end(), std::greater<Fighter>());
	}

	//set champs (top ovr fighters in each weight class)
	for (int i = 0; i < size; i++)
	{
		champs[i][0] = &Fighters[i][0];
		champs[i][1] = &Fighters[i][1];
		champs[i][0]->SetChamp(true);
		champs[i][1]->SetChamp(true);
		std::cout << weightClasses[i] << " CHAMP: ";
		champs[i][0]->GetName();
		std::cout << std::endl;
		std::cout << weightClasses[i] << " CHAMP: ";
		champs[i][1]->GetName();
		std::cout << std::endl;
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
	//Progress Fighters
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < NUMFIGHTERS; j++) {
			Fighters[i][j].Progress();
		}
		std::sort(Fighters[i].begin(), Fighters[i].end(), std::greater<Fighter>());
	}

	//Matchmaking
	FightFinder();


	//Print Card --for debugging
	for (int i = 0; i < 10; i++) {

		std::cout << "index = " << i << std::endl;
		FightCardVec[i].PrintCard();

	}

	//Fight Card
	//Make sure it isn't the first month
	if (Roster::firstMonth)
		Roster::firstMonth = false;
	else {

		std::cout << current << std::endl;

		FightCardVec[current].RunCard(champs);

		//see if champs won or lost their fights

	}

	if (current++ >= 9) current = 0;

	PercentFight();

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
				Fighters[i][j].NewFighter(classWeights[i], i);
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

			//if fighter is a champ, find top contender, or older popular fighter
			//if belts are unified 
			if (champs[i][1] == NULL && Fighters[i][j].isEqual(*champs[i][0])) {
				
				//try to get a money fight first
				for (int k = NUMFIGHTERS - 1; k >= 0; k--) {

					//make sure oponent isnt himself
					if (!Fighters[i][k].GetChamp()) {

						//test if fighter already has fight scheduled and skip
						if (Fighters[i][k].GetHasFight()) continue;

						//check for money fight
						if (Fighters[i][k].GetAttribute(3, 0, false) > 75 && !Fighters[i][k].GetProspect() && rng::randd(0.0,1.0,false) < .8) {

							//std::cout << "\"Money\" title fight" << std::endl;

							//So fight time will be between 3-4 months
							FightMake(&Fighters[i][j], &Fighters[i][k], rng::randd(3.0, 4.0, false));

							break;

						}

					}

				}

				//secondly, a fight against a top contender will sell well too (>60 overall)
				for (int k = NUMFIGHTERS - 1; k >= 0; k--) {

					if (Fighters[i][k].GetHasFight()) continue;

					// will not accept fighter with less than 60 overall
					if (Fighters[i][k].overall < 60) break;

					//check for champ, prospect, or having fight
					if (Fighters[i][k].GetChamp() || Fighters[i][k].GetProspect()) continue;

					//see if fight gets accepted
					if (rng::randd(0.0,1.0,false) > .50) {

						//std::cout << "\"top level\" title fight" << std::endl;

						
						//So fight time will be between 3-4 months
						FightMake(&Fighters[i][j], &Fighters[i][k], rng::randd(3.0, 4.0, false));

						break;

					}

				}

				continue;

			}

			//if fighter is a champ that isn't unified
			if (champs[i][1] != NULL && (Fighters[i][j].isEqual(*champs[i][0]) || Fighters[i][j].isEqual(*champs[i][1]))) {

				//try to get unification bout first
				//make sure champ is not fighting himself
				if (Fighters[i][j].isEqual(*champs[i][0]) && !champs[i][1]->GetHasFight() && rng::randd(0.0, 1.0, false) < .8) {

					//std::cout << "\"unification\" title fight" << std::endl;

					// fight time will be between 3-4 months
					FightMake(&Fighters[i][j], champs[i][1], rng::randd(3.0, 4.0, false));

					continue;

				}else if (Fighters[i][j].isEqual(*champs[i][1]) && !champs[i][0]->GetHasFight() && rng::randd(0.0, 1.0, false) < .8) {

					//std::cout << "\"unification\" title fight" << std::endl;

					// fight time will be between 3-4 months
					FightMake(&Fighters[i][j], champs[i][0], rng::randd(3.0, 4.0, false));

					continue;

				}

				//try to get a money fight 
				for (int k = NUMFIGHTERS - 1; k >= 0; k--) {

					//make sure oponent isnt himself
					if (!Fighters[i][k].GetChamp()) {

						//test if fighter already has fight scheduled and skip
						if (Fighters[i][k].GetHasFight()) continue;

						//check for money fight
						if (Fighters[i][k].GetAttribute(3, 0, false) > 75 && !Fighters[i][k].GetProspect() && rng::randd(0.0, 1.0, false) < .8) {

							//std::cout << "\"Money\" title fight" << std::endl;

							//So fight time will be between 3-4 months
							FightMake(&Fighters[i][j], &Fighters[i][k], rng::randd(3.0, 4.0, false));

							break;

						}

					}

				}

				//secondly, a fight against a top contender will sell well too (>60 overall)
				for (int k = NUMFIGHTERS - 1; k >= 0; k--) {

					if (Fighters[i][k].GetHasFight()) continue;

					// will not accept fighter with less than 60 overall
					if (Fighters[i][k].overall < 60) break;

					//check for champ, prospect, or having fight
					if (Fighters[i][k].GetChamp() || Fighters[i][k].GetProspect()) continue;

					//see if fight gets accepted
					if (rng::randd(0.0, 1.0, false) > .50) {

						//std::cout << "\"top level\" title fight" << std::endl;


						//So fight time will be between 3-4 months
						FightMake(&Fighters[i][j], &Fighters[i][k], rng::randd(3.0, 4.0, false));


					}

				}

				continue;

			}

			//if fighter is a prospect; find "can"
			if (Fighters[i][j].GetProspect()) {

				//if fighter overall isnt about 20; find any low level opponent
				if (Fighters[i][j].overall < 20) {

					for (int k = NUMFIGHTERS - 1; k >= 0; k--) {

						//test if fighter already has fight scheduled and skip
						if (Fighters[i][k].GetHasFight()) continue;

						//make sure fighter isnt a prospect and doesn't have a fight scheduled
						if (!Fighters[i][k].GetProspect() && !Fighters[i][k].GetHasFight()) {

							//std::cout << "Prospect fight" << std::endl;

							//Fight time for prospects seems to be lower than most
							//So fight time will be between 1-2 months
							FightMake(&Fighters[i][j], &Fighters[i][k], rng::randd(1.0, 2.0, false));

							break;

						}

					}

				}

				float ovrDif = rng::randd(8.0, 12.0, false);

				//Find fight for prospect will ~random overall difference
				for (int k = 0; k < NUMFIGHTERS; k++) {

					//Prospect will have 85% chance of taking fight
					if ((Fighters[i][j].overall > (Fighters[i][k].overall + ovrDif)) && !Fighters[i][k].GetHasFight() && rng::randd(0.0, 1.0, false) < .85) {

						//std::cout << "Prospect fight" << std::endl;

						//Fight time for prospects seems to be lower than most
						//So fight time will be between 1-2 months
						FightMake(&Fighters[i][j], &Fighters[i][k], rng::randd(1.0, 2.0, false));

						break;

					}

				}

				continue;

			}

			//Fighters with high success close to retirement will look for easier "money fights"
			if (Fighters[i][j].GetAttribute(6, false, 0) > 35 && Fighters[i][j].GetAttribute(9, false, 0) > 80 && !Fighters[i][j].GetHasFight()) {

				//Find fighter with high popularity and lower overall
				for (int k = 0; k < NUMFIGHTERS; k++) {

					float ovrDif = rng::randd(5.0, 10.0, false);

					//Popularity cutoff is 80; Overall difference must be >5
					//Fighter has a good chance of taking this fight as it will be very profitable (90%)
					if (Fighters[i][k].GetAttribute(3, false, 0) > 80 && (Fighters[i][j].overall - ovrDif) >= Fighters[i][k].overall && rng::randd(0.0, 1.0, false) < .90 && !Fighters[i][k].GetHasFight()) {

						//std::cout << "Late career money fight" << std::endl;

						//Big name fights like this will have a longer build up time than most
						FightMake(&Fighters[i][j], &Fighters[i][k], rng::randd(3.0, 6.0, false));

						break;

					}

				}

				continue;

			}

			//Top level fighters will attempt to find fights close in ovr(+-10)
			//They will also take fights more rarely than other fighters
			//*top level includes 70+ overall
			if (Fighters[i][j].overall > 60 && !Fighters[i][j].GetHasFight()) {

				for (int k = 0; k < NUMFIGHTERS; k++) {

					if (Fighters[i][j].isEqual(Fighters[i][k])) continue;

					//50% chance for fight to make
					if ((Fighters[i][j].overall - Fighters[i][k].overall < rng::randd(8.0, 12.0, false) || Fighters[i][k].overall - Fighters[i][j].overall < rng::randd(8.0, 12.0, false)) && !Fighters[i][k].GetHasFight() && rng::randd(0.0,1.0,false) > .5) {

						//std::cout << "Top Level Fight" << std::endl;

						//Big name fights like this will have a longer build up time than most
						FightMake(&Fighters[i][j], &Fighters[i][k], rng::randd(3.0, 6.0, false));

						break;

					}

				}

				continue;

			}

			//All other fighters will match up evenly and have a pretty short time to fight
			//and a high chance of acceptence
			if(!Fighters[i][j].GetHasFight()) {

				for (int k = 0; k < NUMFIGHTERS; k++) {

					if (Fighters[i][j].isEqual(Fighters[i][k])) continue;

					//50% chance for fight to make
					if ((Fighters[i][j].overall - Fighters[i][k].overall < rng::randd(8.0, 12.0, false) || Fighters[i][k].overall - Fighters[i][j].overall < rng::randd(8.0, 12.0, false)) && !Fighters[i][k].GetHasFight() && rng::randd(0.0, 1.0, false) < .7) {

						//std::cout << "Mid-Low Level Fight" << std::endl;

						//Mid-low level fights will have quick camps
						FightMake(&Fighters[i][j], &Fighters[i][k], rng::randd(2.0, 4.0, false));

						break;

					}

				}

				continue;

			}
			
		}

	}

}

void Roster::FightMake(Fighter* f1, Fighter* f2, int wait)
{

	//std::cout << wait << "    " << current << std::endl;

	f1->SetHasFight(true);
	f2->SetHasFight(true);

	int index = 0;

	if (wait + current > 9) index = (wait - (9 - current));
	else index = current + wait;

	FightCardVec[index].AddFight(f1, f2);
}

void Roster::PercentFight()
{
	int sumsum = 0;
	int sum[size];
	for (int i = 0; i < size; i++) sum[i] = 0;

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < NUMFIGHTERS; j++) {

			if (Fighters[i][j].GetHasFight()) {
				sum[i]++;
				sumsum++;
			}
		}
	}

	float percentTot = float(sumsum) / (size * NUMFIGHTERS);

	std::cout << "% of roster that has fight: " << percentTot << std::endl;

}

Roster::~Roster()
{

}