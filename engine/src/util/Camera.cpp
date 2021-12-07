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

std::pair<float, float> Camera::getWorldDimensions() const { return {mWorldRight, mWorldTop}; }

void Camera::setWorldDimensions(float right, float top, float left, float bottom)
{
        mWorldLeft = left;
        mWorldRight = right;
        mWorldTop = top;
        mWorldBottom = bottom;
}

std::pair<float, float> Camera::getWindowDimensions() const { return {mWindowRight, mWindowBottom}; }

void Camera::setWindowDimensions(float right, float bottom, float left, float top)
{
        mWindowLeft = left;
        mWindowRight = right;
        mWindowTop = top;
        mWindowBottom = bottom;
}

std::pair<float, float> Camera::transform(float x, float y) const
{
        // Transform x coordinate
        float windowX = ((mWindowRight - mWindowLeft) / (mWorldRight - mWorldLeft)) * x -
                        ((mWindowRight - mWindowLeft) / (mWorldRight - mWorldLeft) * mWorldLeft - mWindowLeft);

        // Transform y coordinate
        float windowY = ((mWindowBottom - mWindowTop) / (mWorldBottom - mWorldTop)) * y -
                        ((mWindowBottom - mWindowTop) / (mWorldBottom - mWorldTop) * mWorldTop - mWindowTop);

        return {windowX, windowY};
}

std::pair<float, float> Camera::inverseTransform(float x, float y) const
{
        // Transform x coordinate
        float A = ((mWindowRight - mWindowLeft) / (mWorldRight - mWorldLeft));
        float worldX = ((mWindowRight - mWindowLeft) / (mWorldRight - mWorldLeft) * mWorldLeft - mWindowLeft) + x;
        worldX /= A;

        // Transform y coordinate
        float B = ((mWindowBottom - mWindowTop) / (mWorldBottom - mWorldTop));
        float worldY = ((mWindowBottom - mWindowTop) / (mWorldBottom - mWorldTop) * mWorldTop - mWindowTop) + y;
        worldY /= B;

        return {worldX, worldY};
}

void Camera::move(float x, float y)
{
        mCameraX = x;
        if (y < 0) {
                return;
        }
        mCameraY = y;
}

float Camera::getX() const { return mCameraX; }

float Camera::getY() const { return mCameraY; }

float Camera::getMaxHeight() const { return mMaxHeight; }

bool Camera::isMaxHeight(float height)
{
        if (height < mWorldTop / 2.f)
                return false;
        if (height >= mMaxHeight) {
                mMaxHeight - mLastMaxHeight;
                mMaxHeight = height;
                Observer::Subject::trigger();
                return true;
        }
        return false;
}
