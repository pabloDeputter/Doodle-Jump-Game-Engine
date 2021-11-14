//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_STOPWATCH_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_STOPWATCH_H

#include <cfloat>
#include <chrono>

namespace Utils {

class Stopwatch
{
private:
        std::chrono::high_resolution_clock::time_point s_time;

private:
        Stopwatch() = default;

        static Stopwatch& Get();

        float IDelta();

public:
        Stopwatch(const Stopwatch&) = delete;

        Stopwatch& operator=(const Stopwatch&) = delete;

        static float Delta();
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_STOPWATCH_H
