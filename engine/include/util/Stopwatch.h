//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_STOPWATCH_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_STOPWATCH_H

#include "model/Entity.h"

#include <cfloat>
#include <chrono>
#include <iostream>
#include <map>

/**
 * @brief Namespace holds all Utilities
 */
namespace Utils {
/**
 * @brief Class for Stopwatch implemented using singleton pattern
 */
class Stopwatch
{
private:
        std::chrono::high_resolution_clock::time_point mTime; /**< Last recorded time point */
        float mDeltaTime; /**< Time between two recorded time points in milliseconds */
        std::map<Model::Type, std::pair<float, std::chrono::high_resolution_clock::time_point>>
            mTimers; /**< Active timers */
public:
        /**
         * @brief Constructor for Stopwatch object
         */
        Stopwatch() : mDeltaTime(0.f) {}

public:
        /**
         * @brief Default destructor for Stopwatch object
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
        void start() { mTime = std::chrono::high_resolution_clock::now(); }
        /**
         * @brief Lap one round and return found delta
         * @return float - delta
         */
        [[nodiscard]] float lap();
        /**
         * @brief Get latest delta
         * @return float
         */
        [[nodiscard]] float getDelta() const { return mDeltaTime; }
        /**
         * @brief Reset Stopwatch
         */
        void reset() { mTimers.clear(); }
        /**
         * @brief Add timer to Stopwatch
         * @param key int - used to create Model::Type instance
         * @param amount float - duration of timer
         */
        void addTimer(unsigned int key, float amount);
        /**
         * @brief Check if timer had expired
         * @param key int - used to create Model::Type instance
         * @return true - if timer has expired
         */
        bool checkTimer(unsigned int key);
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_STOPWATCH_H
