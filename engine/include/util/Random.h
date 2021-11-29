//
// Created by Pablo Deputter on 11/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_RANDOM_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_RANDOM_H

#include <random>

namespace Utils {
// TODO - ik heb hier gewerkt met interface functions --> moet eig getInstance()
class Random
{
private:
        Random() = default;

        float IRandom(float a, float b) const;

        static Random& Get();

public:
        ~Random() = default;

        Random(const Random&) = delete;

        Random& operator=(const Random&) = delete;

        static Random& GetInstance();

        static float GetRandom(float a, float b);
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_RANDOM_H
