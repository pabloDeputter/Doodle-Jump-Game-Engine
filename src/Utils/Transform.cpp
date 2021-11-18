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

void Transform::ISetDimensions(float width, float height)
{
        mWindowHeight = width;
        mWindowWidth = height;
}

std::pair<float, float> Transform::IGetDimensions() const { return std::make_pair(mWindowHeight, mWindowWidth); }

void Transform::SetDimensions(float width, float height) { Get().ISetDimensions(width, height); }

std::pair<float, float> Transform::GetDimensions() { return Get().IGetDimensions(); }