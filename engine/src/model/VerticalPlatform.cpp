//
// Created by Pablo Deputter on 05/12/2021.
//

#include "model/VerticalPlatform.h"

#include "util/Stopwatch.h"

using namespace Model;

void VerticalPlatform::initBounds()
{
        // Move from between fixed vertical height
        const float offset = Utils::Random::getInstance().random(.7f, 1.5f);
        mBounds = {mY - offset, mY + offset};
        mInit = true;
}

void VerticalPlatform::move(bool collision)
{
        // If bounds are not yet initialized --> initialize bounds
        if (!mInit) {
                initBounds();
        }

        if (mY >= mBounds.second) {
                mMovingDown = false;
        } else if (mY <= mBounds.first) {
                mMovingDown = true;
        }

        if (mMovingDown) {
                Entity::move(0.f, mSpeed * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f);
        } else {
                Entity::move(0.f, -mSpeed * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f);
        }
}
