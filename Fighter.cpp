
#include "Fighter.h"

Fighter::Fighter()
{

}

void Fighter::CreateFighter(int ovr, int wght, int index)
{

	Fighter::weight = wght;
	Fighter::weightIndex = index;

	//------ Generating -------

	//-- PERSONAL --

	//age
	static const int minAge = 18;
	static const int maxAge = 44;
	Fighter::age = rng::probCurve(minAge, maxAge, .2);

	//overall
	const int tempOverall = rng::varianceRand(ovr, 3.0, 0, 100);

	//career
	Fighter::career = static_cast<int>((Fighter::age - minAge) * (tempOverall / 100.0));

	//xfac
	Fighter::xfac = (-30 * log10
	(rng::randd(0, 40, true) + 1.0)) + 100;
	if (Fighter::xfac < tempOverall) Fighter::xfac = tempOverall;

	//longevity
	Fighter::longevity = rng::varianceRand(Fighter::xfac, 20.0, 0, 100);

	//motivation
	Fighter::motivation = rng::varianceRand(Fighter::xfac, 20.0, 0, 100);

	//peakStart
	Fighter::peakStart = rng::randd(22, 32, false);

	//name
	Fighter::first = Fighter::SelectName(false);
	Fighter::last = Fighter::SelectName(true);

	//-- PHYSICAL ATTRIBUTES --

	//height
	Fighter::height = rng::randd(0, 100, false);

	//reach
	Fighter::reach = rng::varianceRand(Fighter::height, 50.0, 0, 100);

	//stamina
	Fighter::stamina = rng::varianceRand(tempOverall, 5.0, 0, 100);

	//health
	Fighter::health = rng::varianceRand(tempOverall, 5.0, 0, 100);

	//power
	Fighter::power = rng::varianceRand(tempOverall, 5.0, 0, 100);

	//speed
	Fighter::speed = rng::varianceRand(tempOverall, 5.0, 0, 100);

	//timing
	Fighter::timing = rng::varianceRand(tempOverall, 5.0, 0, 100);

	//defense
	Fighter::defense = rng::varianceRand(tempOverall, 5.0, 0, 100);

	//footwork
	Fighter::footwork = rng::varianceRand(tempOverall, 5.0, 0, 100);

	//overall
	Fighter::CalculateOverall();

	//-- CAREER --

	//fights
	Fighter::fights = rng::varianceRand(Fighter::career * 4, 20.0, Fighter::career, Fighter::career * 7);

	//wins
	if (career <= 5)
		Fighter::wins = rng::varianceRand((Fighter::fights * (Fighter::overall * 3)) / 100, 2.0, 0, Fighter::fights);
	else
		Fighter::wins = (Fighter::fights * Fighter::overall) / 100;

	//draws
	Fighter::draws = rng::randd(0, (fights - wins) / 2, false);

	//losses
	Fighter::losses = fights - (wins + draws);

	//Success
	Fighter::success = (Fighter::wins * 2.5) - (Fighter::losses * 5) - (Fighter::draws * 2);
	if (Fighter::success > 100) Fighter::success = 100;
	else if (Fighter::success < 0) Fighter::success = 0;

	//popularity
	int personality = rng::randd(0.0, 100.0, false);
	int prospect = 0;
	if (Fighter::GetProspect()) prospect = 25;
	Fighter::popularity = (Fighter::success / 25.0) + prospect + (Fighter::power / 50 + Fighter::speed / 50) + rng::randd(0.0, 25.0, false);
	if (personality > Fighter::popularity)Fighter::popularity = personality;


	//damage
	Fighter::damage = (((Fighter::wins * rng::randd(1, 1.5, false)) + (Fighter::losses * rng::randd(2, 4, false)) + (Fighter::draws * rng::randd(1.5, 2, false))));
	
	//peak status
	Fighter::peakStatus = Fighter::DeterminePeak();

	//initialize changes
	for (int i = 0; i < 10; i++)
		Fighter::changes[i] = 0;

	//isChamp
	Fighter::isChamp = false;

	//hasfight
	Fighter::hasFight = false;

	//lastfight
	Fighter::lastFight = false;

}

void Fighter::NewFighter(int wght, int index)
{
	Fighter::weight = wght;
	Fighter::weightIndex = index;

	//------ Generating -------

	//-- PERSONAL --

	//name
	Fighter::first = Fighter::SelectName(false);
	Fighter::last = Fighter::SelectName(true);

	//age
	static const int minAge = 18;
	static const int maxAge = 22;
	Fighter::age = rng::probCurve(minAge, maxAge, .66);

	//overall
	const int tempOverall = (8000 * (1 / ((rng::randd(0, 70, false) + 75))) - 55);
	std::cout << "tempovr: " << tempOverall << std::endl;

	//career
	Fighter::career = 0;

	//xfac
	Fighter::xfac = (-25 * log10(rng::randd(0, 100, true) + 1.0)) + 100;

	//longevity
	Fighter::longevity = (24.0 * (Fighter::xfac * rng::randd(0.7, 1, false))) / 100;

	//motivation
	Fighter::motivation = rng::randd(75, 100, false);

	//popularity -- needs belt system first
	//success -- needs belt system first

	//-- PHYSICAL ATTRIBUTES --

	//height
	Fighter::height = rng::randd(0, 100, false);

	//reach
	Fighter::reach = rng::varianceRand(Fighter::height, 20.0, 0, 100);

	//stamina
	Fighter::stamina = rng::randd(20.0, 100.0, false);

	//health
	Fighter::health = rng::randd(20.0, 100.0, false);

	//power
	Fighter::power = rng::randd(20.0, 100.0, false);

	//speed
	Fighter::speed = rng::randd(20.0, 100.0, false);

	//timing
	Fighter::timing = rng::varianceRand(tempOverall, 10.0, 0, 100);

	//defense
	Fighter::defense = rng::varianceRand(tempOverall, 10.0, 0, 100);

	//footwork
	Fighter::footwork = rng::varianceRand(tempOverall, 10.0, 0, 100);

	//overall
	Fighter::CalculateOverall();

	//-- CAREER --

	//fights
	Fighter::fights = 0;

	//wins
	Fighter::wins = 0;

	//draws
	Fighter::draws = 0;

	//losses
	Fighter::losses = 0;

	//damage
	Fighter::damage = 0;

	//peak status
	Fighter::peakStatus = 0;

	//initialize changes
	for (int i = 0; i < 10; i++)
		Fighter::changes[i] = 0;

	//isChamp
	Fighter::isChamp = false;

	//hasfight
	Fighter::hasFight = false;

	//lastfight
	Fighter::lastFight = false;

}

std::string Fighter::SelectName(bool last)
{

	std::ifstream names;
	std::string line = "";

	if (!last)
	{
		//first name
		names.open("resources/firstnames.txt");
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
		names.open("resources/lastnames.txt");
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

int Fighter::DeterminePeak()
{
	if (Fighter::peakStatus == 2 && Fighter::age > Fighter::peakStart)
		return 2;
	
	if (Fighter::age < Fighter::peakStart)
		return 0;
	else if (Fighter::age == Fighter::peakStart)
		return 1;
	else {

		int peakLength = Fighter::age - Fighter::peakStart;
		int peakEndFactor = rng::randd(peakLength * 3, peakLength * 10, true);
		//std::cout << peakEndFactor + (Fighter::age / 3) << " > " << (Fighter::longevity + Fighter::motivation) / 2.5 << std::endl;
		if (peakEndFactor + (Fighter::age / 3) > (Fighter::longevity + Fighter::motivation) / 2) {
			return 2;
		}
		else return 1;

	}

}

void Fighter::Progress()
{

	for (int i = 0; i <= 8; i++)
		Fighter::changes[i] = 0;

	int current = 0;
	float amb = (Fighter::motivation / 100.0) + (Fighter::xfac / 100.0);
	//std::cout << amb << std::endl;

	float band = 5.0 / (Fighter::xfac - Fighter::overall);
	//std::cout << "rubber band effect: " << band << std::endl;
	if (band > .75 || band <= 0) band = .75;


	if (Fighter::peakStatus == 0) {

		//--phys

		//stamina
		current = ((amb / (band*2)) * pow(rng::randd(0.0, 1.0, false), 3.0));
		if ((current > 0 && Fighter::stamina >= 100) || ((Fighter::stamina + current) >= 100))
			Fighter::stamina = 100;
		else if ((Fighter::stamina + current) >= 100) {
			changes[0] = 100 - Fighter::stamina;
			Fighter::stamina = 100;
		}
		else {
			Fighter::stamina += current;
			changes[0] = current;
		}
		
		//speed
		current = ((amb / (band * 2)) * pow(rng::randd(0.0, 1.0, false), 3.0));
		if ((current > 0 && Fighter::speed >= 100) || ((Fighter::speed + current) >= 100))
			Fighter::speed = 100;
		else if ((Fighter::speed + current) >= 100) {
			changes[1] = 100 - Fighter::speed;
			Fighter::speed = 100;
		}
		else {
			Fighter::speed += current;
			changes[1] = current;
		}

		//--mental
		
		//timing
		current = ((amb / band) * pow(rng::randd(0.0, 1.0, false), 3.0));
		if ((current > 0 && Fighter::timing >= 100) || ((Fighter::timing + current) >= 100))
			Fighter::timing = 100;
		else if ((Fighter::timing + current) >= 100) {
			changes[3] = 100 - Fighter::timing;
			Fighter::timing = 100;
		}
		else {
			Fighter::timing += current;
			changes[3] = current;
		}

		//defense
		current = ((amb / band) * pow(rng::randd(0.0, 1.0, false), 3.0));
		if ((current > 0 && Fighter::defense >= 100) || ((Fighter::defense + current) >= 100))
			Fighter::defense = 100;
		else if ((Fighter::defense + current) >= 100) {
			changes[4] = 100 - Fighter::defense;
			Fighter::defense = 100;
		}
		else {
			Fighter::defense += current;
			changes[4] = current;
		}

		//footwork
		current = ((amb / band) * pow(rng::randd(0.0, 1.0, false), 3.0));
		if ((current > 0 && Fighter::footwork >= 100) || ((Fighter::footwork + current) >= 100))
			Fighter::footwork = 100;
		else if ((Fighter::footwork + current) >= 100) {
			changes[5] = 100 - Fighter::footwork;
			Fighter::footwork = 100;
		}
		else {
			Fighter::footwork += current;
			changes[5] = current;
		}

		//--ambition

		//motivation
		current = ((.8/1.0) * pow(rng::randd(-1.0, 1.0, false), 3.0));
		if ((current > 0 && Fighter::motivation >= 100) || ((Fighter::motivation + current) >= 100))
			Fighter::motivation = 100;
		else if ((Fighter::motivation + current) >= 100) {
			changes[6] = 100 - Fighter::motivation;
			Fighter::motivation = 100;
		}
		else {
			Fighter::motivation += current;
			changes[6] = current;
		}

	}
	else if (Fighter::peakStatus == 1) {

		//--phys

		//stamina
		current = ((1.05/amb) * pow(rng::randd(-1.0, 1.0, false), 3.0));
		if ((current > 0 && Fighter::stamina >= 100) || ((Fighter::stamina + current) >= 100))
			Fighter::stamina = 100;
		else if ((Fighter::stamina + current) >= 100) {
			changes[0] = 100 - Fighter::stamina;
			Fighter::stamina = 100;
		}
		else {
			Fighter::stamina += current;
			changes[0] = current;
		}

		//speed
		current = ((1.05/amb) * pow(rng::randd(-1.0, 1.0, false), 3.0));
		if ((current > 0 && Fighter::speed >= 100) || ((Fighter::speed + current) >= 100))
			Fighter::speed = 100;
		else if ((Fighter::speed + current) >= 100) {
			changes[1] = 100 - Fighter::speed;
			Fighter::speed = 100;
		}
		else {
			Fighter::speed += current;
			changes[1] = current;
		}

		//--mental

		//timing
		current = ((amb / 2.65) * pow(rng::randd(0.0, 1.0, false), 3.0));
		if ((current > 0 && Fighter::timing >= 100) || ((Fighter::timing + current) >= 100))
			Fighter::timing = 100;
		else if ((Fighter::timing + current) >= 100) {
			changes[3] = 100 - Fighter::timing;
			Fighter::timing = 100;
		}
		else {
			Fighter::timing += current;
			changes[3] = current;
		}

		//defense
		current = ((amb / 2.65) * pow(rng::randd(0.0, 1.0, false), 3.0));
		if ((current > 0 && Fighter::defense >= 100) || ((Fighter::defense + current) >= 100))
			Fighter::defense = 100;
		else if ((Fighter::defense + current) >= 100) {
			changes[4] = 100 - Fighter::defense;
			Fighter::defense = 100;
		}
		else {
			Fighter::defense += current;
			changes[4] = current;
		}

		//footwork
		current = ((amb / 2.65) * pow(rng::randd(0.0, 1.0, false), 3.0));
		if ((current > 0 && Fighter::footwork >= 100) || ((Fighter::footwork + current) >= 100))
			Fighter::footwork = 100;
		else if ((Fighter::footwork + current) >= 100) {
			changes[5] = 100 - Fighter::footwork;
			Fighter::footwork = 100;
		}
		else {
			Fighter::footwork += current;
			changes[5] = current;
		}

		//--ambition

		//motivation
		current = ((.8 / 1.0) * pow(rng::randd(-1.0, 1.0, false), 3.0));
		if ((current > 0 && Fighter::motivation >= 100) || ((Fighter::motivation + current) >= 100))
			Fighter::motivation = 100;
		else if ((Fighter::motivation + current) >= 100) {
			changes[6] = 100 - Fighter::motivation;
			Fighter::motivation = 100;
		}
		else {
			Fighter::motivation += current;
			changes[6] = current;
		}

	}
	else if (Fighter::peakStatus == 2) {

		float ageFactor = pow((Fighter::career / 13.0), 2.5) + (100.0 / Fighter::longevity);
		//std::cout << "ageFactor: " << ageFactor << std::endl;

		//--phys

		//stamina
		current = ((ageFactor / (amb / 2.0)) * pow(rng::randd(-1.0, 0.0, false), 3.0));
		if ((current > 0 && Fighter::stamina >= 100) || ((Fighter::stamina + current) >= 100))
			Fighter::stamina = 100;
		else if ((Fighter::stamina + current) >= 100) {
			changes[0] = 100 - Fighter::stamina;
			Fighter::stamina = 100;
		}
		else if ((Fighter::stamina + current) <= 0) {
			changes[0] = Fighter::stamina;
			Fighter::stamina = 0;
		}
		else {
			Fighter::stamina += current;
			changes[0] = current;
		}

		//speed
		current = ((ageFactor / (amb / 2.0)) * pow(rng::randd(-1.0, 0.0, false), 3.0));
		if ((current > 0 && Fighter::speed >= 100) || ((Fighter::speed + current) >= 100))
			Fighter::speed = 100;
		else if ((Fighter::speed + current) >= 100) {
			changes[1] = 100 - Fighter::speed;
			Fighter::speed = 100;
		}
		else if ((Fighter::speed + current) <= 0){
			changes[1] = Fighter::speed;
			Fighter::speed = 0;
		} 
		else {
			Fighter::speed += current;
			changes[1] = current;
		}

		//--mental

		//timing
		current = ((.75 / amb) * pow(rng::randd(-1.0, 0.0, false), 3.0));
		if ((current > 0 && Fighter::timing >= 100) || ((Fighter::timing + current) >= 100))
			Fighter::timing = 100;
		else if ((Fighter::timing + current) >= 100) {
			changes[3] = 100 - Fighter::timing;
			Fighter::timing = 100;
		}
		else {
			Fighter::timing += current;
			changes[3] = current;
		}

		//defense
		current = ((.75 / amb) * pow(rng::randd(-1.0, 0.0, false), 3.0));
		if ((current > 0 && Fighter::defense >= 100) || ((Fighter::defense + current) >= 100))
			Fighter::defense = 100;
		else if ((Fighter::defense + current) >= 100) {
			changes[4] = 100 - Fighter::defense;
			Fighter::defense = 100;
		}
		else {
			Fighter::defense += current;
			changes[4] = current;
		}

		//footwork
		current = ((.75 / amb) * pow(rng::randd(-1.0, 0.0, false), 3.0));
		if ((current > 0 && Fighter::footwork >= 100) || ((Fighter::footwork + current) >= 100))
			Fighter::footwork = 100;
		else if ((Fighter::footwork + current) >= 100) {
			changes[5] = 100 - Fighter::footwork;
			Fighter::footwork = 100;
		}
		else {
			Fighter::footwork += current;
			changes[5] = current;
		}

		//--ambition

		//motivation
		current = ((.8 / 1.0) * pow(rng::randd(-1.0, 1.0, false), 3.0));
		if ((current > 0 && Fighter::motivation >= 100) || ((Fighter::motivation + current) >= 100))
			Fighter::motivation = 100;
		else if ((Fighter::motivation + current) >= 100) {
			changes[6] = 100 - Fighter::motivation;
			Fighter::motivation = 100;
		}
		else {
			Fighter::motivation += current;
			changes[6] = current;
		}

	}

	int temp = Fighter::overall;
	Fighter::CalculateOverall();
	changes[8] = Fighter::overall - temp;

}

int Fighter::GetAttribute(int attribute, bool change, int changeValue)
{

	if (attribute < 0 || attribute > 24)
		throw "attribute out of range";

	if (change)
	{
		switch (attribute)
		{
		case 0: Fighter::overall = changeValue;
			break;
		case 1: Fighter::weight = changeValue;
			break;
		//case 2: Fighter::promotion = changeValue;
			//break;
		//case 3: Fighter::popularity = changeValue;
			//break;
		//case 4: Fighter::belts = changeValue;
			//break;
		case 5: Fighter::damage = changeValue;
			break;
		case 6: Fighter::age = changeValue;
			break;
		case 7: Fighter::career = changeValue;
			break;
		case 8: Fighter::xfac = changeValue;
			break;
		case 9: Fighter::success = changeValue;
			break;
		case 10: Fighter::longevity = changeValue;
			break;
		case 11: Fighter::motivation = changeValue;
			break;
		case 12: Fighter::fights = changeValue;
			break;
		case 13: Fighter::wins = changeValue;
			break;
		case 14: Fighter::losses = changeValue;
			break;
		case 15: Fighter::draws = changeValue;
			break;
		case 16: Fighter::reach = changeValue;
			break;
		case 17: Fighter::height = changeValue;
			break;
		case 18: Fighter::stamina = changeValue;
			break;
		case 19: Fighter::health = changeValue;
			break;
		case 20: Fighter::power = changeValue;
			break;
		case 21: Fighter::speed = changeValue;
			break;
		case 22: Fighter::timing = changeValue;
			break;
		case 23: Fighter::defense = changeValue;
			break;
		case 24: Fighter::footwork = changeValue;
			break;
		}
		return 0;
	}
	else
		switch (attribute)
		{
		case 0: return Fighter::overall;
			break;
		case 1: return Fighter::weight;
			break;
		//case 2: return Fighter::promotion;
			//break;
		case 3: return Fighter::popularity;
			break;
		//case 4: return Fighter::belts;
			//break;
		case 5: return Fighter::damage;
			break;
		case 6: return Fighter::age;
			break;
		case 7: return Fighter::career;
			break;
		case 8: return Fighter::xfac;
			break;
		case 9: return Fighter::success;
			break;
		case 10: return Fighter::longevity;
			break;
		case 11: return Fighter::motivation;
			break;
		case 12: return Fighter::fights;
			break;
		case 13: return Fighter::wins;
			break;
		case 14: return Fighter::losses;
			break;
		case 15: return Fighter::draws;
			break;
		case 16: return Fighter::reach;
			break;
		case 17: return Fighter::height;
			break;
		case 18: return Fighter::stamina;
			break;
		case 19: return Fighter::health;
			break;
		case 20: return Fighter::power;
			break;
		case 21: return Fighter::speed;
			break;
		case 22: return Fighter::timing;
			break;
		case 23: return Fighter::defense;
			break;
		case 24: return Fighter::footwork;
			break;
		}

	return NULL;

}

const bool Fighter::GetHasFight()
{
	return Fighter::hasFight;
}

const bool Fighter::GetChamp()
{
	return Fighter::isChamp;
}

const bool Fighter::GetProspect()
{
	return (Fighter::peakStart - Fighter::age) >= 2;
}

void Fighter::SetChamp(bool b)
{
	Fighter::isChamp = b;
}

void Fighter::GetName()
{
	std::cout << Fighter::first << " " << Fighter::last;
}

int Fighter::GetWeight()
{
	return Fighter::weightIndex;
}

void Fighter::SetHasFight(bool b)
{
	Fighter::hasFight = b;
}

void Fighter::FightResult(int result)
{

	switch (result) {
	case 0: Fighter::wins++;
	case 1: Fighter::losses++;
	case 2: Fighter::draws++;
	}
}

void Fighter::AddDamage(int dam)
{

	Fighter::damage += dam / 7;
	changes[9] = dam / 7;

}

bool Fighter::operator > (const Fighter& str) const
{
	return (Fighter::overall > str.overall);
}

bool Fighter::isEqual(const Fighter &c)
{
	//if (this == &c) std::cout << "is equal---------------" << std::endl;
	return this == &c;
}

bool Fighter::IncrementFighterAge()
{
	Fighter::age++;
	Fighter::career++;
	Fighter::peakStatus = Fighter::DeterminePeak();

	if (Fighter::lastFight)
		return true;

	if (Fighter::age > 40 && Fighter::damage > 80 && Fighter::success < 50) {
		std::cout << "1" << std::endl;
		if (Fighter::hasFight) {
			Fighter::lastFight = true;
			return false;
		}
		return true;
	}
	/*if (Fighter::age > 30 && Fighter::success < 30){
		std::cout << "2" << std::endl;
		if (Fighter::hasFight) {
			Fighter::lastFight = true;
			return false;
		}
		return true;
	}*/
	if (Fighter::damage > 90 && rng::randd(0.0, 1.0, false) > .5) {
		std::cout << "3" << std::endl;
		if (Fighter::hasFight) {
			Fighter::lastFight = true;
			return false;
		}
		return true;
	}
	if (Fighter::damage >= 100) {
		std::cout << "4" << std::endl;
		if (Fighter::hasFight) {
			Fighter::lastFight = true;
			return false;
		}
		return true;
	}
	if (Fighter::age > 40 && rng::randd(0.0, 1.0, false) > .5) {
		std::cout << "5" << std::endl;
		if (Fighter::hasFight) {
			Fighter::lastFight = true;
			return false;
		}
		return true;
	}
	if (rng::randd(0.0, 1.0, false) < 0.005) {
		std::cout << "6" << std::endl;
		if (Fighter::hasFight) {
			Fighter::lastFight = true;
			return false;
		}
		return true;
	}

	return false;
}

void Fighter::CalculateOverall()
{
	if (Fighter::power >= Fighter::speed)
		Fighter::overall = ((Fighter::stamina * 2) + (Fighter::health * 1) + (Fighter::power * 3) + (Fighter::timing * 2) + (Fighter::defense * 2)) / 10;
	else
		Fighter::overall = ((Fighter::stamina * 2) + (Fighter::health * 1) + (Fighter::speed * 3) + (Fighter::timing * 2) + (Fighter::defense * 2)) / 10;

}

void Fighter::PrintFighter()
{
	std::cout << Fighter::first << " " << Fighter::last << ": " << std::endl;
	std::cout << "OVR: " << Fighter::overall << " ";
	std::cout << "CAR: " << Fighter::career << " ";
	std::cout << "PKS: " << Fighter::peakStart << " ";
	std::cout << "PST: " << Fighter::peakStatus << " ";
	std::cout << "AGE: " << Fighter::age << " ";
	std::cout << "LON: " << Fighter::longevity << " ";
	std::cout << "MOT: " << Fighter::motivation << " ";
	std::cout << "XFC: " << Fighter::xfac << " ";
	std::cout << "DAM: " << Fighter::damage << " " << std::endl;
	std::cout << "HGT: " << Fighter::height << " ";
	std::cout << "RCH: " << Fighter::reach << " ";
	std::cout << "STA: " << Fighter::stamina << " ";
	std::cout << "HTH: " << Fighter::health << " ";
	std::cout << "PWR: " << Fighter::power << " ";
	std::cout << "SPD: " << Fighter::speed << " ";
	std::cout << "TIM: " << Fighter::timing << " ";
	std::cout << "FWK: " << Fighter::footwork << " ";
	std::cout << "DEF: " << Fighter::defense << " " << std::endl;

	std::cout << Fighter::wins << "-" << Fighter::losses;
	std::cout << "-" << Fighter::draws << std::endl;
}

void Fighter::PrintAttribute(int att,int val, int change, bool newLine) 
{

	std::string attributes[] = { "OVR", "WGT", "PRO", "POP" , "BEL" , "DAM" , "AGE" ,
					  "CAR" , "POT" , "SUC" , "LON" , "MOT" , "FIG" , "WIN", "LOS",
					  "DRW" , "RCH" , "HGT" , "STA" , "HTH" , "PWR" , "SPD", "TIM",
					  "DEF", "FWK" };


	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int k = 15;

	if (change > 0) 
		k = 10;
	else if (change < 0)
		k = 12;

	SetConsoleTextAttribute(hConsole, k);

	std::cout <<  attributes[att];
	std::cout << ": " << val << " (";
	if (change > 0) std::cout << "+";
	std::cout << change;
	std::cout << ") ";

	k = 15;

	SetConsoleTextAttribute(hConsole, k);

	if (newLine)
		std::cout << std::endl;
	else
		std::cout << " -- ";

}

void Fighter::vPrint()
{
	std::cout << Fighter::first << " " << Fighter::last << ": " << std::endl;

	std::cout << "WGT: " << Fighter::weight << " ";
	std::cout << "CAR: " << Fighter::career << " ";
	std::cout << "PKS: " << Fighter::peakStart << " ";
	std::cout << "PST: " << Fighter::peakStatus << " ";
	std::cout << "AGE: " << Fighter::age << " ";
	std::cout << "XFC: " << Fighter::xfac << " " << std::endl;

	Fighter::PrintAttribute(0, Fighter::overall, changes[8], false);
	Fighter::PrintAttribute(3, Fighter::popularity, 0, false);
	Fighter::PrintAttribute(9, Fighter::success, 0, false);
	Fighter::PrintAttribute(10, Fighter::longevity, changes[7], false);
	Fighter::PrintAttribute(11, Fighter::motivation, changes[6], false);
	Fighter::PrintAttribute(5, Fighter::damage, changes[9], true);
	Fighter::PrintAttribute(18, Fighter::stamina, changes[0], false);
	Fighter::PrintAttribute(19, Fighter::health, 0, false);
	Fighter::PrintAttribute(20, Fighter::power, 0, false);
	Fighter::PrintAttribute(21, Fighter::speed, changes[1], true);
	Fighter::PrintAttribute(22, Fighter::timing, changes[3], false);
	Fighter::PrintAttribute(23, Fighter::defense, changes[4], false);
	Fighter::PrintAttribute(24, Fighter::footwork, changes[5], true);

	std::cout << Fighter::wins << "-" << Fighter::losses;
	std::cout << "-" << Fighter::draws << std::endl;
	 
}

Fighter::~Fighter()
{

}
