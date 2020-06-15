#include "RNG.h"
#include <random>
#include <math.h>
#include <stdlib.h>
#include <iostream>

namespace rng {

    float randd(float low, float high, bool contain)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(low, high);

        if (contain && dist(mt) < 0.05)
            return 0.05;


        return dist(mt);
    }

    float bellCurve(float position, float height, float length, int half, bool inverse)
    {
        float inverseCurve = -1.0;
        if (inverse)
            inverseCurve = 1.0;

        if (inverse && (position > length))
            return height;
        else if (!inverse && (position > length))
            return 0;

        switch (half)
        {
        case 0:
            return ((inverseCurve * height / 2) * cos((9.87 * position) / ((length / 2) * PI))) + (height / 2);
        case 1:
            if (position > length / 2)
                return height;
            else
                return ((inverseCurve * height / 2) * cos((9.87 * position) / ((length / 2) * PI))) + (height / 2);
        case 2:
            if (position < length / 2)
                return height;
            else
                return ((inverseCurve * height / 2) * cos((9.87 * position) / ((length / 2) * PI))) + (height / 2);
        default:
            return 0;
        }
    }

    int probCurve(int low, int high, float weight)
    {
        int length = high - low;
        int num = 0;

        while (true)
        {
            for (int i = 0; i < length; i++)
                if (randd(0, 1, false) < bellCurve(i, weight, length, 0, false))
                {
                    num = i;
                    break;
                }
            if (num) return (num + low);
        }
    }

    int varianceRand(int root, float var, int low, int high)
    {
        int final = root + randd(-var, var, false);
        if (final > high) final = high;
        else if (final < low) final = low;
        return final;
    }

}
