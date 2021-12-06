//
// Created by Pablo Deputter on 05/12/2021.
//

#include "model/HorizontalPlatform.h"

using namespace Model;

Model::Type HorizontalPlatform::getType() const { return Model::eHorizontal; }

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
                Entity::move(.01f * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f, 0.f);
        } else {
                Entity::move(-.01f * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f, 0.f);
        }
}

void HorizontalPlatform::initBounds()
{
        const float offset = Utils::Random::getInstance().random(.4f, .9f);
        mBounds = {mX - offset, mX + offset};
        mInit = true;
}