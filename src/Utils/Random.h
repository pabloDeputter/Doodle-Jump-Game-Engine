//
// Created by Pablo Deputter on 11/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_RANDOM_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_RANDOM_H

class Random
{
private:
        float r_random = 0.25f;

        float IFloat() const;

        Random() = default;

public:
        Random(const Random&) = delete;

        Random& operator=(const Random&) = delete;

        static Random& Get();

        static float GetRandom();
};

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_RANDOM_H
