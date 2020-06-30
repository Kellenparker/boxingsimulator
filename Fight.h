#include "Fighter.h"

#pragma once

class Fight
{
	struct fighters
	{
		int reach;
		int height;
		int stamina;
		int speed;
		int timing;
		int power;
		int defense;
		int footwork;
		int health;
	};

	int attendence;
	
	//represents how good the fight is
	int score;

public:
	Fight(Fighter *f1, Fighter *f2);

	~Fight();

};

