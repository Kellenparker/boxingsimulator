#pragma once

class WeightClass
{
private:
    static const int NUMFIGHTERS = 10;

public:

    // Constructor
    WeightClass(int w);

    // ProgressClass: progresses every fighter's attributes
    void ProgressClass();

    // IncrementAge: adds a year to every fighter's age
    void IncrementAge();

    // Deconstructor
    ~WeightClass();
};

