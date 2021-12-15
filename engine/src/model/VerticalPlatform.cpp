//
// Created by Pablo Deputter on 05/12/2021.
//

#include "model/VerticalPlatform.h"
#include "util/Stopwatch.h"

using namespace Model;

void VerticalPlatform::move(bool collision)
{
        if (!mInit) {
                initBounds();
        }

        if (mBounds.first == 0.f && mBounds.second == 0.f) {
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

void VerticalPlatform::initBounds()
{
        const float offset = Utils::Random::getInstance().random(.7f, 1.5f);
        mBounds = {mY - offset, mY + offset};
        mInit = true;
}
