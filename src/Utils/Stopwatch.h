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
        std::chrono::high_resolution_clock::time_point mTime;

private:
        Stopwatch() = default;

        static Stopwatch& Get();

        float IDelta();

        void IStart();

public:
        Stopwatch(const Stopwatch&) = delete;

        Stopwatch& operator=(const Stopwatch&) = delete;

        static float Delta();

        static void Start();
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_STOPWATCH_H
