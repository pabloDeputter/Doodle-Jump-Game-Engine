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

        std::chrono::duration<float> delta = std::chrono::high_resolution_clock::now() - mTime;
        // TODO - reset
        //        mTime = std::chrono::high_resolution_clock::now();
        return delta.count();
}

void Stopwatch::IStart() { mTime = std::chrono::high_resolution_clock::now(); }

float Stopwatch::Delta() { return Get().IDelta(); }

void Stopwatch::Start() { Get().IStart(); }
