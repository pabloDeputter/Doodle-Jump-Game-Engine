//
// Created by Pablo Deputter on 11/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_RANDOM_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_RANDOM_H

namespace Utils {

class Random
{
private:
        float r_random = 0.25f;

        Random() = default;

        float IFloat() const;

        static Random& Get();

public:
        Random(const Random&) = delete;

        Random& operator=(const Random&) = delete;

        static float GetRandom();
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_RANDOM_H
