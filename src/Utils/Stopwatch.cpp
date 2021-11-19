//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Stopwatch.h"

using namespace Utils;

Stopwatch& Stopwatch::Get()
{
        static Stopwatch instance;
        return instance;
}

float Stopwatch::IDelta()
{
        std::chrono::duration<float> ms_delta = std::chrono::high_resolution_clock::now() - mTime;
        // Reset / lap stopwatch
        mTime = std::chrono::high_resolution_clock::now();
        mDeltaTime = ms_delta.count();
        // Return milliseconds as float
        return mDeltaTime;
}

float Stopwatch::IGetDelta() { return mDeltaTime; }

void Stopwatch::IStart() { mTime = std::chrono::high_resolution_clock::now(); }

float Stopwatch::Delta() { return Get().IDelta(); }

float Stopwatch::GetDelta() { return Get().IGetDelta(); }

void Stopwatch::Start() { Get().IStart(); }
