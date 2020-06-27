#pragma once

#include <string>

class Roster {


public:
    Roster();
    void Progress();
    int GetOverall();
    void IncrementAge();
    void PrintWeightClass(int w);
    void FightFinder();
    void FightPrint(int index);
    ~Roster();
};
