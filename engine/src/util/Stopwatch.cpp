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

void Stopwatch::start() { mTime = std::chrono::high_resolution_clock::now(); }

float Stopwatch::lap()
{
        std::chrono::duration<float> ms_delta = std::chrono::high_resolution_clock::now() - mTime;
        // Reset / lap stopwatch
        mTime = std::chrono::high_resolution_clock::now();
        mDeltaTime = ms_delta.count();
        // Return milliseconds as float
        return mDeltaTime;
}

float Stopwatch::getDelta() const { return mDeltaTime; }
