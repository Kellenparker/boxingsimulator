#pragma once

#include <string>

class Fighter
{
	// --VARIABLES--

	//details
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
	int changes[10];

	//next fight status
	bool hasFight;

	//next fight is last fight
	bool lastFight;

	// --FUNCTIONS--

	// SelectName: generates random name for fighter
	std::string SelectName(bool last);

	// DeterminePeak: Determines whether to advance a fighter's peak phase
	// Returns: 0: pre-peak, 1: peak, 2:post-peak
	int DeterminePeak();

	// PrintAttribute: Prints one attribute for vPrint
	void PrintAttribute(int att, int val, int change, bool newLine);

public:
	// Constructor
	Fighter();

	// Deconstructer
	~Fighter();

	// CreateFighter: used to initially fill the weightclasses
	// Pre-Conditions:
	void CreateFighter(int ovr, int wght);

	// NewFighter:
	// Pre-Conditions:
	void NewFighter(int weight);

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
	// If true; Fighter has retired
	bool IncrementFighterAge();

	// CalculateOverall: Executes overall formula stores in RandFighter::Overall
	void CalculateOverall();

	// PrintFighter: Prints fighter information to console
	void PrintFighter();

	// GetName: Prints fighter name
	void GetName();

	// GetProspect: returns if fighter is considered a prospect
	bool GetProspect();

	// GetHasFight: Returns true if fighter already has a fight
	bool GetHasFight();

	// SetHasFight: Sets hasFight to desired boolean value
	void SetHasFight(bool b);

	// FightResult: Updates fighter and record after fight
	// Result: 0 = win; 1 = loss; 2 = draw
	void FightResult(int result);

	// AddDamage: Adds damage based on how tough fight was
	void AddDamage(int dam);

	//overall
	int overall;

	//operator >: provides an operator to use for sorting
	bool operator > (const Fighter& str) const;

	//isEqual: returns if classes are the same
	bool isEqual(const Fighter &c);
	
	// vPrintFighter: Provides a verbose printout of the fighter
	void vPrint();
};

