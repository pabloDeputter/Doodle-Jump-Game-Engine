//
// Created by Pablo Deputter on 11/11/2021.
//

#include "Random.h"

using namespace Utils;

float Random::IFloat() const { return r_random; }

Random& Random::Get()
{
        static Random instance;
        return instance;
}

float Random::GetRandom() { return Get().IFloat(); }
