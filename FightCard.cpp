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

	//f1 should be higher, if not, switch them
	if (fighter2->overall > fighter1->overall) {
		//std::cout << "flippng overalls" << std::endl;
		Fighter* temp = fighter2;
		fighter2 = fighter1;
		fighter1 = temp;
	}

	if (fighter1->isEqual(*fighter2)) {
		std::cout << std::endl << std::endl << std::endl << std::endl << "no";
	}

	std::cout << "Time Until Fight: " << 0 << " months." << std::endl;

	std::cout << "Fighter 1: ";
	fighter1->vPrint();

	std::cout << "Fighter 2: ";
	fighter2->vPrint();

	std::cout << "-------------------------------------------------" << std::endl;

	if (currentSize == 0) {
		fightList[0][0] = fighter1;
		fightList[0][1] = fighter2;
		currentSize++;
		return;
	}

	int sortInd;
	//get index where fighter should be placed
	for (sortInd = 0; sortInd < currentSize; sortInd++)
		if (fighter1->overall > fightList[sortInd][0]->overall) break;

	//move fighters down array to make space for new fighter
	for (int i = currentSize; i >= sortInd; i--) {
		fightList[i + 1][0] = fightList[i][0];
		fightList[i + 1][1] = fightList[i][1];
	}

	fightList[sortInd][0] = fighter1;
	fightList[sortInd][1] = fighter2;

	currentSize++;
}

void FightCard::RunCard(Fighter* champList[][2])
{
	fightSt result;
	Fighter* localChamps[2];

	//Fight card attributes
	float hype = detHype();
	int attendence;
	if (hype < .4) attendence = 25000 * (hype / .4);
	else attendence = 25000;
	int ticketPrice;
	if (attendence < 25000) ticketPrice = 20;
	else ticketPrice = ((hype - .4) * 100) + 20;
	int ppvsales = NULL;
	if (hype > .5) {
		std::cout << "here" << std::endl;
		ppvsales = ((hype * 10) - 5) * 200000;
	}
	int earnings = (attendence * ticketPrice) + (ppvsales * 60);

	int totPop = 0;

	std::cout << "___HYPE___" << hype << "___ATT___" << attendence << "___TIC___" << ticketPrice << "___PPV___" << ppvsales << "___EARN___" << earnings << std::endl;

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

	int fighterEarnings = earnings / 2;
	std::cout << "FE:  " << fighterEarnings << std::endl;

	//give fighters their earnings
	for (int i = 0; i < currentSize; i++) {
		totPop += fightList[i][0]->GetAttribute(3, 0, false);
		totPop += fightList[i][1]->GetAttribute(3, 0, false);
	}

	//std::cout << "totPop =========== " << totPop << std::endl;

	float percentage;

	for (int i = 0; i < currentSize; i++) {
		//add earnings for both fighters
		percentage = fightList[i][0]->GetAttribute(3, 0, false) / float(totPop);

		fightList[i][0]->AddEarnings(fighterEarnings * percentage);

		percentage = fightList[i][1]->GetAttribute(3, 0, false) / float(totPop);

		fightList[i][1]->AddEarnings(fighterEarnings * percentage);
	}

	//empty card
	for (int i = 0; i < MAXSIZE; i++) {
		fightList[i][0] = NULL;
		fightList[i][1] = NULL;
	}

	currentSize = 0;
}

FightCard::fightSt FightCard::RunFight(Fighter* f1, Fighter* f2)
{
	FightCard::fightSt newfight;

	int score = rng::randd(0.0, 100.0, false);

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

	float prob = f1->overall * (1.0 / (f1->overall + f2->overall));

	std::cout << "should be <= " << prob + .1 << std::endl;

	int f1dam, f2dam;

	if (rng::randd(0.0, 1.0, false) <= prob) {
		f1->GetName();
		std::cout << " wins!" << std::endl;

		f1->FightResult(0, score);
		f2->FightResult(1, score);
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

		f1->FightResult(1, score);
		f2->FightResult(0, score);
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

float FightCard::detHype()
{
	float hypeWeight[] = { .50, .30, .1, .1 };
	float sum = 0;

	for (int i = 0; i < 4 && i < currentSize; i++) {
		sum += (float(fightList[i][0]->GetAttribute(3, 0, false) + float(fightList[i][1]->GetAttribute(3, 0, false))) / 200.0) * hypeWeight[i];

		//std::cout << "\t\t____HYPE_____SUM_____" << sum << std::endl;
	}

	return sum;
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

	for (int i = 0; i < currentSize; i++) {
		std::cout << "\t";
		if (fightList[i][0]->GetChamp() || fightList[i][1]->GetChamp())
			std::cout << "Title Fight: ";
		fightList[i][0]->GetName();
		std::cout << " (" << fightList[i][0]->overall << ") ";
		std::cout << " vs. ";
		fightList[i][1]->GetName();
		std::cout << " (" << fightList[i][1]->overall << ") ";
		std::cout << std::endl;
	}
}

FightCard::~FightCard()
{
}