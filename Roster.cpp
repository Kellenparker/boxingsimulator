#include "Roster.h"
#include "WeightClass.h"
#include "RNG.h"
#include <vector>
#include <iostream>
#include <string>

std::vector<WeightClass> RosterVector;

Roster::Roster()
{

	static const std::string weightClasses[] = { "flyweight", "bantamweight", "featherweight", "lightweight" , "welterweight", "middleweight" , "lightheavyweight", "cruiserweight" , "heavyweight" };

	static const int classWeights[] = { 112, 118, 126, 135, 147, 160, 175, 200, 220 };

	static const int size = sizeof(weightClasses);

	RosterVector.resize(size);
	
	for (int i = 0; i > size; i++) {

		RosterVector[i].CreateFighters(classWeights[i]);

	}

}

void Roster::IncrementAge()
{

}

void Roster::Progress()
{

}

Roster::~Roster()
{

}