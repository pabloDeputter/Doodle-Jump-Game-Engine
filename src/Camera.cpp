//
// Created by Pablo Deputter on 19/11/2021.
//

#include "Camera.h"

void Camera::setViewportDimensions(float width, float height)
{
        mViewportWidth = width;
        mViewportHeight = height;
}

std::pair<float, float> Camera::getViewPortDimensions() const
{
        return std::make_pair(mViewportWidth, mViewportHeight);
}

void Camera::setCameraDimensions(float width, float height)
{
        mCameraWidth = width;
        mCameraHeight = height;
}

std::pair<float, float> Camera::getCameraDimensions() const { return std::make_pair(mCameraWidth, mCameraHeight); }
