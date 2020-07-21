#include "FightCard.h"

FightCard::FightCard()
{

	FightCard::currentSize = 0;

}

void FightCard::AddFight(Fighter* fighter1, Fighter* fighter2) 
{

	if (currentSize >= MAXSIZE) {

		std::cout << "AddFight: error: Not enough room in card " << std::endl;
		return;

	}

	fightList[currentSize][0] = fighter1;
	fightList[currentSize][1] = fighter2;
	currentSize++;

}

void FightCard::RunCard(Fighter* champList[][2])
{
	fightSt result;
	Fighter* localChamps[2];

	for (int i = 0; i < currentSize; i++) {

		result = RunFight(fightList[i][0], fightList[i][1]);

		localChamps[0] = champList[result.weight][0];
		localChamps[1] = champList[result.weight][1];

		if (!result.winner->GetChamp() && !result.loser->GetChamp()) continue; //if neither are champs, pass
		else if (result.winner->GetChamp() && result.loser->GetChamp()) { // unification bout

			champList[result.weight][0] = result.winner;
			champList[result.weight][1] = NULL;
			result.loser->SetChamp(false);

			std::cout << "-----------1: NEW CHAMPION: ";
			champList[result.weight][0]->GetName();
			std::cout << std::endl;
			continue;

		}

		//if belts are unified and champ lost
		if (localChamps[1] == NULL && localChamps[0]->isEqual(*result.loser)) {

			champList[result.weight][0] = result.winner;
			result.winner->SetChamp(true);
			result.loser->SetChamp(false);

			std::cout << "---------- - 2: NEW CHAMPION: ";
			result.winner->GetName();
			std::cout << std::endl;
			continue;

		}
		
		//regular (champ vs contenter) bout
		if (localChamps[0]->isEqual(*result.loser)) {

			champList[result.weight][0] = result.winner;
			result.winner->SetChamp(true);
			result.loser->SetChamp(false);

			std::cout << "-----------3: NEW CHAMPION: ";
			champList[result.weight][0]->GetName();
			std::cout << std::endl;
			continue;

		}
		else if (localChamps[1]->isEqual(*result.loser)) {

			champList[result.weight][1] = result.winner;
			result.winner->SetChamp(true);
			result.loser->SetChamp(false);

			std::cout << "---------- - 4: NEW CHAMPION: ";
			result.winner->GetName();
			std::cout << std::endl;

		}

	}

	//empty card
	for (int i = 0; i < MAXSIZE; i++) {

		fightList[i][0] = NULL;
		fightList[i][1] = NULL;

	}

	currentSize = 0;

}

FightCard::fightSt FightCard::RunFight(Fighter *f1, Fighter *f2)
{

	FightCard::fightSt newfight;
	newfight.fight[0] = newfight.fight[1] = 0;

	int attendence = 0;
	int score = 0;

	newfight.weight = f1->GetWeight();

	std::cout << "Fight!!!" << std::endl;

	if (f1->GetChamp()) std::cout << "CHAMPION: ";
	std::cout << "f1: ";
	f1->GetName();
	std::cout << "ovr: " << f1->overall << std::endl;

	if (f2->GetChamp()) std::cout << "CHAMPION: ";
	std::cout << "f2: ";
	f2->GetName();
	std::cout << "ovr: " << f2->overall << std::endl;

	//f1 should be higher, if not, switch them
	if (f2->overall > f1->overall) {

		std::cout << "flippng overalls" << std::endl;
		Fighter temp = *f2;
		f2 = f1;
		*f1 = temp;

		std::cout << "f1: ";
		f1->GetName();
		std::cout << "ovr: " << f1->overall << std::endl;

		std::cout << "f2: ";
		f2->GetName();
		std::cout << "ovr: " << f2->overall << std::endl;

	}

	float prob = f1->overall * (1.0 / (f1->overall + f2->overall));

	std::cout << "should be <= " << prob + .1 << std::endl;

	int f1dam, f2dam;

	if (rng::randd(0.0, 1.0, false) <= prob) {

		f1->GetName();
		std::cout << " wins!" << std::endl;

		f1->FightResult(0);
		f2->FightResult(1);
		newfight.winner = f1;
		newfight.loser = f2;

		f1dam = rng::randd(0.0, 50.0, false);
		f1->AddDamage(f1dam);

		f2dam = rng::randd(25.0, 100.0, false);
		f2->AddDamage(f2dam);

		std::cout << "Damage: winner: " << f1dam << " loser: " << f2dam << std::endl;

	}
	else { 

		f2->GetName();
		std::cout << " wins!" << std::endl;

		f1->FightResult(1);
		f2->FightResult(0);
		newfight.winner = f2;
		newfight.loser = f1;

		f2dam = rng::randd(0.0, 50.0, false);
		f2->AddDamage(f2dam);

		f1dam = rng::randd(25.0, 100.0, false);
		f1->AddDamage(f1dam);

		std::cout << "Damage: winner: " << f2dam << " loser: " << f1dam << std::endl;

	}

	f1->SetHasFight(false);
	f2->SetHasFight(false);

	return newfight;
	
}

void FightCard::FightPrint(int index, int time)
{

	if (index == -1) index = currentSize - 1;

	std::cout << "Time Until Fight: " << time << " months." << std::endl;

	std::cout << "Fighter 1: ";
	fightList[index][0]->vPrint();

	std::cout << "Fighter 2: ";
	fightList[index][1]->vPrint();

	std::cout << "-------------------------------------------------" << std::endl;

}

void FightCard::PrintCard()
{

	std::cout << "Fights: " << std::endl;

	if (currentSize == 0) return;

	for (int i = 0; i < currentSize; i++){

		std::cout << "\t";
		if (fightList[i][0]->GetChamp() || fightList[i][1]->GetChamp())
			std::cout << "Title Fight: ";
		fightList[i][0]->GetName();
		std::cout << " vs. ";
		fightList[i][1]->GetName();
		std::cout << std::endl;

	}

}

FightCard::~FightCard()
{


}
