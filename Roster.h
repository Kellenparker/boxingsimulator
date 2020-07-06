#pragma once

#include <string>
#include "Fighter.h"

class Roster {

    int current;
    bool firstMonth = true;

public:
    Roster();
    void Progress();
    int GetOverall();
    void IncrementAge();
    void PrintWeightClass(int w);
    void FightFinder();
    void FightMake(Fighter *f1, Fighter *f2, int wait);
    ~Roster();
};
