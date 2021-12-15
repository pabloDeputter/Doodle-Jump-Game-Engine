//
// Created by Pablo Deputter on 14/11/2021.
//

#include "util/Stopwatch.h"

using namespace Utils;

Stopwatch& Stopwatch::getInstance()
{
        static Stopwatch instance;
        return instance;
}

float Stopwatch::lap()
{
        std::chrono::duration<float> ms_delta = std::chrono::high_resolution_clock::now() - mTime;
        // Reset / lap stopwatch
        mTime = std::chrono::high_resolution_clock::now();
        mDeltaTime = ms_delta.count();
        // Return milliseconds as float
        return mDeltaTime;
}

void Stopwatch::addTimer(unsigned int key, float amount)
{
        //        if (mTimers.find(Model::Type(key)) != std::end(mTimers)) {
        //        }
        // Add timer
        mTimers[Model::Type(key)] = {amount, std::chrono::high_resolution_clock::now()};
}

bool Stopwatch::checkTimer(unsigned int key)
{
        // If there isn't a active timer for given key, return false
        if (mTimers.find(Model::Type(key)) == std::end(mTimers)) {
                return false;
        }
        auto val = mTimers[Model::Type(key)];
        std::chrono::duration<float> ms_delta = std::chrono::high_resolution_clock::now() - val.second;
        // If timer is not yet expired, return false
        if (ms_delta.count() > val.first) {
                mTimers.erase(Model::Type(key));
                return false;
        }
        return true;
}