//
// Created by Pablo Deputter on 11/11/2021.
//

#include "util/Random.h"

using namespace Utils;

Random& Random::getInstance()
{
        static Random instance;
        return instance;
}

float Random::GetRandom(float a, float b)
{
        // Create random number generator
        std::random_device random_device;
        // Seed random engine
        std::mt19937 random_engine(random_device());
        // Create random distribution
        std::binomial_distribution();
        std::uniform_real_distribution<float> uniformRealDistribution(a, b);

        return uniformRealDistribution(random_engine);
}
