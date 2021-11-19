//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_STOPWATCH_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_STOPWATCH_H

#include <cfloat>
#include <chrono>

/**
 * @brief Namespace holds all Utils
 */
namespace Utils {

class Stopwatch
{
private:
        std::chrono::high_resolution_clock::time_point mTime;
        float mDeltaTime;

private:
        Stopwatch() = default;

        static Stopwatch& Get();

        float IDelta();

        float IGetDelta();

        void IStart();

public:
        Stopwatch(const Stopwatch&) = delete;

        Stopwatch& operator=(const Stopwatch&) = delete;

        static float Delta();

        static float GetDelta();

        static void Start();
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_STOPWATCH_H
