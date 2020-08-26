#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <windows.h>
#include "RNG.h"

class Fighter
{
	// --VARIABLES--

	//details
	int weight;
	int weightIndex;
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
	
	//earnings made from fights
	int earnings;

	//physical attributes
	//1 - 100
	int reach, height, stamina, health, power, speed, timing, defense, footwork;

	//change array
	int changes[10];

	//next fight status
	bool hasFight;

	//wait period before fighting again
	int waitTime;

	//next fight is last fight
	bool lastFight;

	//is fighter a champ
	bool isChamp;

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
	void CreateFighter(int ovr, int wght, int index);

	// NewFighter:
	// Pre-Conditions:
	void NewFighter(int weight, int index);

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

	// vPrintFighter: Provides a verbose printout of the fighter
	void vPrint();

	// GetName: Prints fighter name
	void GetName();

	// GetWeight: Returns a fighters weight index
	int GetWeight();

	// GetProspect: returns if fighter is considered a prospect
	const bool GetProspect();

	// GetHasFight: Returns true if fighter already has a fight
	const bool GetHasFight();

	// GetWait: returns true if fighter is waiting for fight
	const bool GetWait();

	// GetChamp: Returns true if fighter is a champion
	const bool GetChamp();

	// SetChamp: Sets the fighters champ status
	void SetChamp(bool b);

	// SetHasFight: Sets hasFight to desired boolean value
	void SetHasFight(bool b);

	// AddEarnings: adds earnings to total worth
	void AddEarnings(int earn);

	// FightResult: Updates fighter and record after fight
	// Result: 0 = win; 1 = loss; 2 = draw
	void FightResult(int result, int score);

	// AddDamage: Adds damage based on how tough fight was and determines wait time until accepting next fight
	void AddDamage(int dam);

	//overall
	int overall;

	//operator >: provides an operator to use for sorting
	bool operator > (const Fighter& str) const;

	//isEqual: returns if classes are the same
	bool isEqual(const Fighter &c);
};

