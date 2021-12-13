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

void Camera::reset()
{
        mCameraX = 0.f;
        mCameraY = 0.f;
        mMaxHeight = 0.f;
        mLastMaxHeight = 0.f;
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

std::pair<float, float> Camera::transform(float x, float y, float left, float top) const
{
        if (left != 0.f && top != 0.f) {

        } else {
                left = mWindowLeft;
                top = mWindowTop;
        }

        // Transform x coordinate
        float windowX = ((mWindowRight - left) / (mWorldRight - mWorldLeft)) * x -
                        ((mWindowRight - left) / (mWorldRight - mWorldLeft) * mWorldLeft - left);

        // Transform y coordinate
        float windowY = ((mWindowBottom - top) / (mWorldBottom - mWorldTop)) * y -
                        ((mWindowBottom - top) / (mWorldBottom - mWorldTop) * mWorldTop - top);

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

bool Camera::isMaxHeight(float height)
{
        if (height < mWorldTop / 2.f)
                return false;
        if (height > mMaxHeight) {
                mLastMaxHeight = mMaxHeight;
                mMaxHeight = height;
                trigger(EventType::NEW_MAX_HEIGHT, std::make_shared<NewMaxHeightEvent>(mLastMaxHeight, mMaxHeight));
                return true;
        }
        return false;
}
