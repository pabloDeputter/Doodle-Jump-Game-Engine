//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_STOPWATCH_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_STOPWATCH_H

#include <cfloat>
#include <chrono>

/**
 * @brief Namespace holds all Utilities
 */
namespace Utils {
/**
 * @brief Class for Stopwatch
 */
class Stopwatch
{
private:
        std::chrono::high_resolution_clock::time_point mTime; /**< Last recorded time point */
        float mDeltaTime{}; /**< Time between two recorded time points in milliseconds */

        /**
         * @brief Private default constructor
         */
        Stopwatch() = default;

public:
        /**
         * @brief Default destructor
         */
        ~Stopwatch() = default;
        /**
         * @brief Deleted copy constructor
         */
        Stopwatch(const Stopwatch&) = delete;
        /**
         * @brief Deleted assignment operator
         * @return Stopwatch
         */
        Stopwatch& operator=(const Stopwatch&) = delete;
        /**
         * @brief Get instance of Stopwatch
         * @return Stopwatch
         */
        static Stopwatch& getInstance();
        /**
         * @brief Start Stopwatch
         */
        void start();
        /**
         * @brief Lap one round and return found delta
         * @return float
         */
        [[nodiscard]] float lap();
        /**
         * @brief Get latest delta
         * @return float
         */
        [[nodiscard]] float getDelta();
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_STOPWATCH_H
