#include "FightCard.h"
#include "Fight.h"
#include "Fighter.h"
#include <iostream>

Fighter* fightList[MAXSIZE][2];

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

void FightCard::RunCard()
{

	for (int i = 0; i < currentSize; i++) {

		Fight fights(fightList[i][0], fightList[i][1]);

	}

	FightCard::~FightCard();

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

FightCard::~FightCard()
{

	delete fightList;

}
