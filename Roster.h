#pragma once

#include <string>
#include "Fighter.h"

class Roster {

    int current;
    bool firstMonth = true;
    //if belts are unified, index 1 will be null.
    Fighter* champs[9][2];

public:
    Roster();
    void Progress();
    int GetOverall();
    void IncrementAge();
    void PrintWeightClass(int w);
    void FightFinder();
    void FightMake(Fighter *f1, Fighter *f2, int wait);
    void PercentFight();
    ~Roster();
};
