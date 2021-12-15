//
// Created by Pablo Deputter on 16/11/2021.
//

#include "model/Bonus.h"

#include "util/Stopwatch.h"

using namespace Model;

void Bonus::initBounds()
{
        // Initialize bounds
        mBounds = {mY - 0.03f, mY + 0.03f};
        mInit = true;
}

void Bonus::move(bool collision)
{
        // If bounds are not ready initialized, initialize them
        if (!mInit) {
                initBounds();
        }
        // If Y-coordinate of Bonus is equal to or exceeds the highest bound --> move down
        if (mY >= mBounds.second) {
                mMovingDown = false;
        }
        // If Y-coordinate of Bonus is equal to or exceeds the lowest bound --> move up
        else if (mY <= mBounds.first) {
                mMovingDown = true;
        }
        if (mMovingDown) {
                Entity::move(0.f, .002f * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f);
        } else {
                Entity::move(0.f, -.002f * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f);
        }
}
