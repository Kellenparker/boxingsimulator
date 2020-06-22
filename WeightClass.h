#pragma once

class WeightClass
{
    static const int NUMFIGHTERS = 5;

public:

    // Constructor
    WeightClass();

    // CreateFighters: creates all the fighters for the weight class
    void CreateFighters(int w);

    // ProgressClass: progresses every fighter's attributes
    void ProgressClass();

    // IncrementAge: adds a year to every fighter's age
    void IncrementAge();

    void PrintFighters(int w);

    // Deconstructor
    ~WeightClass();
};

