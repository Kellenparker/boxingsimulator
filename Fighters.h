#pragma once

#include <string>

class Fighters
{
	// --VARIABLES--

	//details
	//1 - 100
	int overall;
	int weight;
	//1 - 100
	int popularity;
	//1 - 100
	int damage;
	//10 - 100
	int age;
	int career;
	//1 - 100
	int xfac;
	//1 - 100
	int success;
	//1 - 100
	int longevity;
	//1 - 100
	int motivation;
	//22 - 32
	int peakStart;

	//0: pre peak, 1: peak, 2: post peak
	int peakStatus;

	//name
	std::string first;
	std::string last;

	//record (depends on age mostly)
	int fights;
	int wins, losses, draws;

	//physical attributes
	//1 - 100
	int reach, height, stamina, health, power, speed, timing, defense, footwork;

	//change array
	int changes[7];


	// --FUNCTIONS--

	// SelectName: generates random name for fighter
	std::string SelectName(bool last);

public:
	// Constructor
	Fighters();

	// Deconstructer
	~Fighters();

	// CreateFighter: used to initially fill the weightclasses
	// Pre-Conditions:
	void CreateFighter(int ovr, int wght);

	// NewFighter:
	// Pre-Conditions:
	void NewFighter(int weight);

	// DeterminePeak: Determines whether to advance a fighter's peak phase
	// Returns: 0: pre-peak, 1: peak, 2:post-peak
	int DeterminePeak();

	// Progress: progresses fighter attributes one month
	void Progress();

	// GetAttribute: returns and/or changes a certain attribute
	// Pre-Conditions: 0 <= attribute <= 23; 0 <= changeValue <= 100;
	/*
	get attribute key:
	0 = overall; 1 = weight; 2 = promotion; 3 = popularity;
	4 = belts; 5 = damage; 6 = age; 7 = career; 8 = potential;
	9 = success; 10 = longevity; 11 = motivation; 12 = fights;
	13 = wins; 14 = losses; 15 = draws; 16 = reach; 17 = height;
	18 = stamina; 19 = health; 20 = power; 21 = speed;
	22 = timing; 23 = defense;
	*/
	int GetAttribute(int attribute, bool change, int changeValue);

	// IncrementFigherAge: Adds one year to figher's age
	void IncrementFighterAge();

	// CalculateOverall: Executes overall formula stores in RandFighter::Overall
	void CalculateOverall();

	// PrintFighter: Prints fighter information to console
	void PrintFighter();
	
	// vPrintFighter: Provides a verbose printout of the fighter
	void vPringFighter();
};

