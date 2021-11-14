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

        std::chrono::duration<float, std::milli> float_delta =
            std::chrono::high_resolution_clock::now() - Stopwatch::s_time;
        return float_delta.count();
}

float Stopwatch::Delta() { return Get().IDelta(); }
