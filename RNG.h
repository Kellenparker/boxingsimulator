#pragma once

namespace rng {

    static constexpr auto PI = 3.141526;

    // randd: creates a random number between given values.
    // Arguments: contain: sets a floor value for randd
    float randd(float low, float high, bool contain);

    // bellCurve: returns cos(x)
    // Arguments: position: acts as x in f(x) = cos(x)
    //            height: sets max height for cos
    //            length: sets how long curve is
    //            half: sections off certain half of curve:
    //                      0 - no half; 1 - front half; 2 - back half
    //            inverse: flips curve
    float bellCurve(float position, float height, float length, int half, bool inverse);

    // probCurve: 
    int probCurve(int low, int high, float weight);


    // varianceRand: returns a slightly modified value of given integer
    // Arguments: root: number to be based on
    //            var: amount of variance
    //            high: sets a ceiling value
    //            low: sets a floor value
    int varianceRand(int  root, float var, int low, int high);

}
