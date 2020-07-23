#pragma once

#include "Fighter.h"
#include "RNG.h"
#include <iostream>

#define MAXSIZE 30

class FightCard
{
public:
	struct fightSt {
		int weight;
		Fighter* winner;
		Fighter* loser;
	};

private:

	Fighter* fightList[MAXSIZE][2];
	// ^ and v are to share indexes.
	int hype[MAXSIZE];

	int currentSize;

public:

	FightCard();

	void AddFight(Fighter *fighter1, Fighter *fighter2);

	void RunCard(Fighter* champList[][2]);

	fightSt RunFight(Fighter *f1, Fighter *f2);

	void FightPrint(int index, int time);

	void PrintCard();

	~FightCard();

};

