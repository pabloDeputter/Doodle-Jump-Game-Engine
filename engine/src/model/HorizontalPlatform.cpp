//
// Created by Pablo Deputter on 05/12/2021.
//

#include "model/HorizontalPlatform.h"
#include "util/Camera.h"
#include "util/Stopwatch.h"

using namespace Model;

void HorizontalPlatform::move(bool collision)
{
        if (!mInit) {
                initBounds();
        }

        if (mX >= mBounds.second) {
                mMovingForward = false;
        } else if (mX <= mBounds.first) {
                mMovingForward = true;
        }

        if (mMovingForward) {
                Entity::move(mSpeed * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f, 0.f);
        } else {
                Entity::move(-mSpeed * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f, 0.f);
        }
}

void HorizontalPlatform::initBounds()
{
        //        const float offset = Utils::Random::getInstance().random(.7f, 1.5f);
        //        mBounds = {mX - offset, mX + offset};
        // Move from left to right
        mBounds = {0.f, Utils::Camera::getInstance().getWorldDimensions().first};

        mInit = true;
}