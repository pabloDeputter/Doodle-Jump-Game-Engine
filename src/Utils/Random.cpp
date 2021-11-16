//
// Created by Pablo Deputter on 11/11/2021.
//

#include "Random.h"

using namespace Utils;

Random& Random::Get()
{
        static Random instance;
        return instance;
}
