#include "Roster.h"
#include "WeightClass.h"
#include "RNG.h"
#include <vector>
#include <iostream>
#include <string>

std::vector<WeightClass> RosterVector;

static const std::string weightClasses[] = { "flyweight", "bantamweight", "featherweight", "lightweight" , "welterweight", "middleweight" , "lightheavyweight", "cruiserweight" , "heavyweight" };

static const int classWeights[] = { 112, 118, 126, 135, 147, 160, 175, 200, 220 };

const int size = 9;

Roster::Roster()
{

	RosterVector.resize(size);
	
	for (int i = 0; i < size; i++) {

		RosterVector[i].CreateFighters(classWeights[i]);

	}

}

void Roster::Progress()
{
	for (int i = 0; i < size; i++) {
		std::cout << "ind " << i << std::endl;
		RosterVector[i].ProgressClass();
	}
}

void Roster::IncrementAge()
{
	for (int i = 0; i < size; i++)
		RosterVector[i].IncrementAge();
}

void Roster::PrintWeightClass(int w)
{
	
	RosterVector[w].PrintFighters();

}

Roster::~Roster()
{

}