//
// Created by Pablo Deputter on 06/12/2021.
//

#include "model/Jetpack.h"

using namespace Model;

Model::Type Model::Jetpack::getType() const { return Model::eJetpack; }

void Jetpack::move(bool collision)
{
        // TODO - jetpack
        if (mStarted) {
                if (Utils::Stopwatch::getInstance().checkTimer(Model::eJetpack)) {
                        std::cout << "jetpackStopped\n";
                }
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

void Jetpack::initBounds()
{
        mBounds = {mY - 0.03f, mY + 0.03f};
        mInit = true;
}
