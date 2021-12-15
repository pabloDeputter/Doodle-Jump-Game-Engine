//
// Created by Pablo Deputter on 16/11/2021.
//

#include "model/Bonus.h"
#include "util/Stopwatch.h"

using namespace Model;

void Bonus::move(bool collision)
{
        // TODO - jetpack
        if (mStarted) {
                return;
        }

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
                Entity::move(0.f, .002f * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f);
        } else {
                Entity::move(0.f, -.002f * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f);
        }
}

void Bonus::initBounds()
{
        mBounds = {mY - 0.03f, mY + 0.03f};
        mInit = true;
}