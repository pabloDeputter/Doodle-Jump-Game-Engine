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

enum Type
{
        ePlayer = 0,
        eBonus = 1,
        eStatic = 2,
        eHorizontal = 3,
        eVertical = 4,
        eTemporary = 5,
        eBackground = 6,
        eJetpack = 7,
        eSpring = 8
};

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
        std::map<Type, std::pair<float, std::chrono::high_resolution_clock::time_point>> mTimers;

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
        [[nodiscard]] float getDelta() const;

        // TODO - jetpack
        void addTimer(unsigned int key, float amount)
        {
                std::cout << "addTimer\n";
                if (mTimers.find(Type(key)) != std::end(mTimers)) {
                        std::cout << "ERROR\n";
                }
                mTimers[Type(key)] = {amount, std::chrono::high_resolution_clock::now()};
        }
        //        std::chrono::duration<float> ms_delta = std::chrono::high_resolution_clock::now() - mTime;
        //        // Reset / lap stopwatch
        //        mTime = std::chrono::high_resolution_clock::now();
        //        mDeltaTime = ms_delta.count();
        //        // Return milliseconds as float
        //        return mDeltaTime;
        bool checkTimer(unsigned int key)
        {
                if (mTimers.find(Type(key)) == std::end(mTimers)) {
                        std::cout << "ERROR\n";
                        return false;
                }
                auto val = mTimers[Type(key)];
                std::chrono::duration<float> ms_delta = std::chrono::high_resolution_clock::now() - val.second;
                std::cout << ms_delta.count() << "\n";
                if (ms_delta.count() > val.first) {
                        //                        mTimers.erase(Type(key));
                        return true;
                        return true;
                }
                return false;
        }
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_STOPWATCH_H
