#include "data_types.hpp"

namespace wad{
    std::vector<ThingType> thing_types = {
        {ENEMY, {68, 64, 3003, 3005, 72, 16, 3002, 65, 69, 3001, 3006, 67, 66, 71, 9, 58, 7, 84, 3004}},
        {WEAPON, {2006, 2002, 2005, 2004, 2003, 2001, 82}},
        {AMMO, {2008, 2048, 2046, 2049, 2007, 2047, 17, 2010}},
        {ARTIFACT, {2015, 2023, 2026, 2014, 2022, 2045, 83, 2024, 2013}},
        {POWERUP, {2018, 8, 2012, 2019, 2025, 2011}},
        {KEY, {5, 40, 13, 38, 6, 39}},
        {OBSTACLE, {47, 70, 43, 35, 41, 2035, 28, 42, 2028, 53, 52, 78, 75, 77, 76, 50, 74, 73, 51, 49, 25, 54, 29, 55, 56, 31, 36, 57, 33, 37, 86, 27, 44, 45, 30, 46, 32, 48, 85, 26}},
        {DECOR, {10, 12, 34, 22, 21, 18, 19, 20, 23, 15, 62, 60, 59, 61, 63, 79, 80, 24, 81}},
        {OTHER, {11, 89, 1, 2, 3, 4, 88, 87, 14}}
    };


    THING_TYPE getThingType(int thing_type) {
        for (const ThingType& thingType : thing_types) {
            if (std::find(thingType.thing_numbers.begin(), thingType.thing_numbers.end(), thing_type) != thingType.thing_numbers.end()) {
                return thingType.type;
            }
        }
        return OTHER;
    }
}