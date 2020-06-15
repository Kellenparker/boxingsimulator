#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Fighters.h"
#include "RNG.h"


Fighters::Fighters()
{

}

void Fighters::CreateFighter(int ovr, int wght)
{

	Fighters::weight = wght;

	//------ Generating -------

	//-- PERSONAL --

	//age
	static const int minAge = 18;
	static const int maxAge = 44;
	Fighters::age = rng::probCurve(minAge, maxAge, .2);

	//overall
	const int tempOverall = rng::varianceRand(ovr, 3.0, 0, 100);

	//career
	Fighters::career = static_cast<int>((Fighters::age - minAge) * (tempOverall / 100.0));

	//xfac
	Fighters::xfac = (-30 * log10
	(rng::randd(0, 40, true) + 1.0)) + 100;
	if (Fighters::xfac < tempOverall) Fighters::xfac = tempOverall;

	//longevity
	Fighters::longevity = rng::varianceRand(Fighters::xfac, 20.0, 0, 100);

	//motivation
	Fighters::motivation = rng::varianceRand(Fighters::xfac, 20.0, 0, 100);

	//peakStart
	Fighters::peakStart = rng::randd(22, 32, false);

	//popularity -- needs belt system first
	//success -- needs belt system first

	//name
	Fighters::first = Fighters::SelectName(false);
	Fighters::last = Fighters::SelectName(true);

	//-- PHYSICAL ATTRIBUTES --

	//height
	Fighters::height = rng::randd(0, 100, false);

	//reach
	Fighters::reach = rng::varianceRand(Fighters::height, 50.0, 0, 100);

	//stamina
	Fighters::stamina = rng::varianceRand(tempOverall, 5.0, 0, 100);

	//health
	Fighters::health = rng::varianceRand(tempOverall, 5.0, 0, 100);

	//power
	Fighters::power = rng::varianceRand(tempOverall, 5.0, 0, 100);

	//speed
	Fighters::speed = rng::varianceRand(tempOverall, 5.0, 0, 100);

	//timing
	Fighters::timing = rng::varianceRand(tempOverall, 5.0, 0, 100);

	//defense
	Fighters::defense = rng::varianceRand(tempOverall, 5.0, 0, 100);

	//footwork
	Fighters::footwork = rng::varianceRand(tempOverall, 5.0, 0, 100);

	//overall
	Fighters::CalculateOverall();

	//-- CAREER --

	//fights
	Fighters::fights = rng::varianceRand(Fighters::career * 4, 20.0, Fighters::career, Fighters::career * 7);

	//wins
	if (career <= 5)
		Fighters::wins = rng::varianceRand((Fighters::fights * (Fighters::overall * 3)) / 100, 2.0, 0, Fighters::fights);
	else
		Fighters::wins = (Fighters::fights * Fighters::overall) / 100;

	//draws
	Fighters::draws = rng::randd(0, (fights - wins) / 2, false);

	//losses
	Fighters::losses = fights - (wins + draws);

	//damage
	Fighters::damage = (((Fighters::wins * rng::randd(1, 1.5, false)) + (Fighters::losses * rng::randd(2, 4, false)) + (Fighters::draws * rng::randd(1.5, 2, false))));

}

void Fighters::NewFighter(int wght)
{
	Fighters::weight = wght;
	//------ Generating -------

	//-- PERSONAL --

	//name
	Fighters::first = Fighters::SelectName(false);
	Fighters::last = Fighters::SelectName(true);

	//age
	static const int minAge = 18;
	static const int maxAge = 22;
	Fighters::age = rng::probCurve(minAge, maxAge, .66);

	//overall
	const int tempOverall = rng::probCurve(0, 100, .05);

	//career
	Fighters::career = 0;

	//xfac
	Fighters::xfac = (-25 * log10(rng::randd(0, 100, true) + 1.0)) + 100;

	//longevity
	Fighters::longevity = (24.0 * (xfac * rng::randd(0.7, 1, false))) / 100;

	//motivation
	Fighters::motivation = rng::randd(75, 100, false);

	//popularity -- needs belt system first
	//success -- needs belt system first

	//-- PHYSICAL ATTRIBUTES --

	//height
	Fighters::height = rng::randd(0, 100, false);

	//reach
	Fighters::reach = rng::varianceRand(Fighters::height, 50.0, 0, 100);

	//stamina
	Fighters::stamina = rng::varianceRand(75, 25.0, 0, 100);

	//health
	Fighters::health = rng::varianceRand(75, 25.0, 0, 100);

	//power
	Fighters::power = rng::varianceRand(75, 25.0, 0, 100);

	//speed
	Fighters::speed = rng::varianceRand(75, 25.0, 0, 100);

	//timing
	Fighters::timing = rng::varianceRand(25, 25.0, 0, 100);

	//defense
	Fighters::defense = rng::varianceRand(25, 25.0, 0, 100);

	//footwork
	Fighters::footwork = rng::varianceRand(tempOverall, 5.0, 0, 100);

	//overall
	Fighters::CalculateOverall();

	//-- CAREER --

	//fights
	Fighters::fights = 0;

	//wins
	Fighters::wins = 0;

	//draws
	Fighters::draws = 0;

	//losses
	Fighters::losses = 0;

	//damage
	Fighters::damage = 0;

}

std::string Fighters::SelectName(bool last)
{

	std::ifstream names;
	std::string line = "";

	if (!last)
	{
		//first name
		names.open("/Users/kellenparker/Documents/Programming projects/fightsim/fightsim/resources/firstnames.txt");
		if (names.is_open())
		{
			for (int i = 0; i < rng::randd(0, 1219, false); i++)
			{
				getline(names, line);
			}
		}
		return line;
	}
	else
	{
		//last names
		names.open("/Users/kellenparker/Documents/Programming projects/fightsim/fightsim/resources/lastnames.txt");
		if (names.is_open())
		{
			for (int i = 0; i < rng::randd(0, 88799, false); i++)
			{
				getline(names, line);
			}
		}
		return line;
	}

}

int Fighters::DeterminePeak()
{
	if (Fighters::peakStatus == 2)
		return 2;

	if (Fighters::age < Fighters::peakStart)
		return 0;
	else if (Fighters::age == Fighters::peakStart)
		return 1;
	else {

		int peakLength = Fighters::age - Fighters::peakStart;
		int peakEndFactor = rng::randd(peakLength * 3, peakLength * 10, true);
		std::cout << peakEndFactor + (Fighters::age / 3) << " > " << (Fighters::longevity + Fighters::motivation) / 2.5 << std::endl;
		if (peakEndFactor + (Fighters::age / 3) > (Fighters::longevity + Fighters::motivation) / 2) {
			return 2;
		}
		else return 1;

	}

}

void Fighters::Progress()
{
	if (Fighters::peakStatus == 0) {



	}
	else if (Fighters::peakStatus == 1) {



	}
	else if (Fighters::peakStatus == 2) {



	}

	Fighters::CalculateOverall();
}

int Fighters::GetAttribute(int attribute, bool change, int changeValue)
{

	if (attribute < 0 || attribute > 24)
		throw "attribute out of range";

	if (change)
	{
		switch (attribute)
		{
		case 0: Fighters::overall = changeValue;
			break;
		case 1: Fighters::weight = changeValue;
			break;
			//case 2: Fighters::promotion = changeValue;
				//break;
			//case 3: Fighters::popularity = changeValue;
				//break;
			//case 4: Fighters::belts = changeValue;
				//break;
		case 5: Fighters::damage = changeValue;
			break;
		case 6: Fighters::age = changeValue;
			break;
		case 7: Fighters::career = changeValue;
			break;
		case 8: Fighters::xfac = changeValue;
			break;
		case 9: Fighters::success = changeValue;
			break;
		case 10: Fighters::longevity = changeValue;
			break;
		case 11: Fighters::motivation = changeValue;
			break;
		case 12: Fighters::fights = changeValue;
			break;
		case 13: Fighters::wins = changeValue;
			break;
		case 14: Fighters::losses = changeValue;
			break;
		case 15: Fighters::draws = changeValue;
			break;
		case 16: Fighters::reach = changeValue;
			break;
		case 17: Fighters::height = changeValue;
			break;
		case 18: Fighters::stamina = changeValue;
			break;
		case 19: Fighters::health = changeValue;
			break;
		case 20: Fighters::power = changeValue;
			break;
		case 21: Fighters::speed = changeValue;
			break;
		case 22: Fighters::timing = changeValue;
			break;
		case 23: Fighters::defense = changeValue;
			break;
		case 24: Fighters::footwork = changeValue;
			break;
		}
		return 0;
	}
	else
		switch (attribute)
		{
		case 0: return Fighters::overall;
			break;
		case 1: return Fighters::weight;
			break;
			//case 2: return Fighters::promotion;
				//break;
			//case 3: return Fighters::popularity;
				//break;
			//case 4: return Fighters::belts;
				//break;
		case 5: return Fighters::damage;
			break;
		case 6: return Fighters::age;
			break;
		case 7: return Fighters::career;
			break;
		case 8: return Fighters::xfac;
			break;
		case 9: return Fighters::success;
			break;
		case 10: return Fighters::longevity;
			break;
		case 11: return Fighters::motivation;
			break;
		case 12: return Fighters::fights;
			break;
		case 13: return Fighters::wins;
			break;
		case 14: return Fighters::losses;
			break;
		case 15: return Fighters::draws;
			break;
		case 16: return Fighters::reach;
			break;
		case 17: return Fighters::height;
			break;
		case 18: return Fighters::stamina;
			break;
		case 19: return Fighters::health;
			break;
		case 20: return Fighters::power;
			break;
		case 21: return Fighters::speed;
			break;
		case 22: return Fighters::timing;
			break;
		case 23: return Fighters::defense;
			break;
		case 24: return Fighters::footwork;
			break;
		}

	return NULL;

}

void Fighters::IncrementFighterAge()
{
	Fighters::age++;
	Fighters::career++;
	Fighters::peakStatus = Fighters::DeterminePeak();
}

void Fighters::CalculateOverall()
{
	if (Fighters::power >= Fighters::speed)
		Fighters::overall = ((Fighters::stamina * 2) + (Fighters::health * 1) + (Fighters::power * 3) + (Fighters::timing * 2) + (Fighters::defense * 2)) / 10;
	else
		Fighters::overall = ((Fighters::stamina * 2) + (Fighters::health * 1) + (Fighters::speed * 3) + (Fighters::timing * 2) + (Fighters::defense * 2)) / 10;

}

void Fighters::PrintFighter()
{
	std::cout << Fighters::first << " " << Fighters::last << ": " << std::endl;
	std::cout << "OVR: " << Fighters::overall << " ";
	std::cout << "CAR: " << Fighters::career << " ";
	std::cout << "PKS: " << Fighters::peakStart << " ";
	std::cout << "AGE: " << Fighters::age << " ";
	std::cout << "LON: " << Fighters::longevity << " ";
	std::cout << "MOT: " << Fighters::motivation << " ";
	std::cout << "XFC: " << Fighters::xfac << " ";
	std::cout << "DAM: " << Fighters::damage << " ";
	std::cout << "HGT: " << Fighters::height << " " << std::endl;
	std::cout << "RCH: " << Fighters::reach << " ";
	std::cout << "STA: " << Fighters::stamina << " ";
	std::cout << "HTH: " << Fighters::health << " ";
	std::cout << "PWR: " << Fighters::power << " ";
	std::cout << "SPD: " << Fighters::speed << " ";
	std::cout << "TIM: " << Fighters::timing << " ";
	std::cout << "FWK: " << Fighters::footwork << " ";
	std::cout << "DEF: " << Fighters::defense << " " << std::endl;

	std::cout << Fighters::wins << "-" << Fighters::losses;
	std::cout << "-" << Fighters::draws << std::endl;
}

Fighters::~Fighters()
{

}
