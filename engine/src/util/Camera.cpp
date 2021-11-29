//
// Created by Pablo Deputter on 19/11/2021.
//

#include "util/Camera.h"

using namespace Utils;

Camera& Camera::getInstance()
{
        static Camera camera;
        return camera;
}

void Camera::setWindowDimensions(float right, float bottom, float left, float top)
{
        mWindowLeft = left;
        mWindowRight = right;
        mWindowTop = top;
        mWindowBottom = bottom;
}

void Camera::setGameDimensions(float right, float bottom, float left, float top)
{
        mGameLeft = left;
        mGameRight = right;
        mGameTop = top;
        mGameBottom = bottom;
}

std::pair<float, float> Camera::transform(float x, float y) const
{
        // Transform x coordinate
        float windowX = ((mWindowRight - mWindowLeft) / (mGameRight - mGameLeft)) * x -
                        ((mWindowRight - mWindowLeft) / (mGameRight - mGameLeft) * 0.f - mWindowLeft);
        // Transform y coordinate
        float windowY = ((mWindowBottom - mWindowTop) / (mGameBottom - mGameTop)) * y -
                        ((mWindowBottom - mWindowTop) / (mGameBottom - mGameTop) * 0.f - mWindowTop);
        return {windowX, windowY};
}

std::pair<float, float> Camera::getPosition() const { return {mCameraX, mCameraY}; }
