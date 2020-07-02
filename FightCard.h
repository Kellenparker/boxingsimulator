#pragma once
#include "Fighter.h"

#define MAXSIZE 30

class FightCard
{

	int currentSize;

public:

	FightCard();

	void AddFight(Fighter *fighter1, Fighter *fighter2);

	void RunCard();

	void FightPrint(int index, int time);

	~FightCard();

};

