#pragma once
#include "Fighter.h"

#define MAXSIZE 30

class FightCard
{

	struct fightSt {
		int fight[2];
	};

	Fighter* fightList[MAXSIZE][2];

	int currentSize;

public:

	FightCard();

	void AddFight(Fighter *fighter1, Fighter *fighter2);

	void RunCard();

	fightSt RunFight(Fighter *f1, Fighter *f2);

	void FightPrint(int index, int time);

	void PrintCard();

	~FightCard();

};

