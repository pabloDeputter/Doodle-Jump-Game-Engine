//
// Created by Pablo Deputter on 15/11/2021.
//

#include "Transform.h"

using namespace Utils;

Transform& Transform::Get()
{
        static Transform instance;
        return instance;
}

void Transform::ISetDimensions(int width, int height)
{
        mWindowHeight = width;
        mWindowWidth = height;
}

void Transform::SetDimensions(int width, int height) { Get().ISetDimensions(width, height); }