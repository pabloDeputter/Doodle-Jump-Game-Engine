//
// Created by Pablo Deputter on 05/12/2021.
//

#include "model/VerticalPlatform.h"

using namespace Model;

Model::Type VerticalPlatform::getType() const { return Model::eVertical; }

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
                Entity::move(0.f, .01f * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f);
        } else {
                Entity::move(0.f, -.01f * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f);
        }
}

void VerticalPlatform::initBounds()
{
        const float offset = Utils::Random::getInstance().random(.4f, .9f);
        mBounds = {mY - offset, mY + offset};
        mInit = true;
}
