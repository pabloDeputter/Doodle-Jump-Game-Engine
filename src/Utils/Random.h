//
// Created by Pablo Deputter on 11/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_RANDOM_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_RANDOM_H

#include <random>

namespace Utils {

class Random
{
private:
        Random() = default;

        template <typename T>
        T IRandom() const
        {
                std::random_device random_device;
                std::mt19937 random_engine(random_device());
                std::normal_distribution<T> normal_distribution;

                return normal_distribution(random_engine);
        }

        static Random& Get();

public:
        Random(const Random&) = delete;

        Random& operator=(const Random&) = delete;

        template <typename T>
        static T GetRandom(T t)
        {
                return Get().template IRandom<T>();
        }
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_RANDOM_H
