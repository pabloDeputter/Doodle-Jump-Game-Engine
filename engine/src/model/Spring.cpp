//
// Created by Pablo Deputter on 06/12/2021.
//

#include "model/Spring.h"

using namespace Model;

Model::Type Model::Spring::getType() const { return Model::eSpring; }

void Spring::move(bool collision)
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
                Entity::move(0.f, .002f * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f);
        } else {
                Entity::move(0.f, -.002f * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f);
        }
}

void Spring::initBounds()
{
        mBounds = {mY - 0.05f, mY + 0.05f};
        mInit = true;
}
