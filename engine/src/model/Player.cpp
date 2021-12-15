//
// Created by Pablo Deputter on 14/11/2021.
//

#include "model/Player.h"

#include "util/Stopwatch.h"

using namespace Model;

void Player::move(bool collision)
{
        // Reset direction of player
        mDirection = std::make_pair(0.f, 0.f);

        // Check if there is a collision
        if (collision) {
                // Direction will be inverted and Player will get max vertical velocity
                mDirection.second = 1.f;
                mVelocity.second = mMaxVelocity;
        }

        // Make Player fall
        if (mState == eNormal && mVelocity.second <= 0) {
                mDirection.second = -1.f;
                if (mVelocity.second > -mMaxVelocity) {
                        mVelocity.second -=
                            mAcceleration * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f;
                }
        } else if (mState == eFlying) {
                mDirection.second = 1.f;
                if (mVelocity.second < mMaxVelocity) {
                        mVelocity.second +=
                            mAcceleration * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f;
                }
        }

        // Increase horizontal velocity
        if (mIsMovingRight) {
                mDirection.first = 1.f;
                if (mVelocity.first < mMaxVelocity) {
                        mVelocity.first +=
                            mAcceleration * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f;
                }
        } else if (mIsMovingLeft) {
                mDirection.first = -1.f;
                if (mVelocity.first > -mMaxVelocity) {
                        mVelocity.first -=
                            mAcceleration * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f;
                }
        }

        // Apply drag to horizontal speed
        if (mVelocity.first > 0.f) {
                mVelocity.first -= mDrag * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f;
                if (mVelocity.first < 0.f) {
                        mVelocity.first = 0.f;
                }
        } else if (mVelocity.first < 0.f) {
                mVelocity.first += mDrag * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f;
                if (mVelocity.first > 0.f) {
                        mVelocity.first = 0.f;
                }
        }
        // Apply drag to vertical speed
        if (mVelocity.second > 0.f) {
                mVelocity.second -= mDrag * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f;
                if (mVelocity.second < 0.f) {
                        mVelocity.second = 0.f;
                }
        } else if (mVelocity.second < 0.f) {
                mVelocity.second += mDrag * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f;
                if (mVelocity.second > 0.f) {
                        mVelocity.second = 0.f;
                }
        }

        // Finally, move Player
        Entity::move(mVelocity.first * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f,
                     mVelocity.second * Utils::Stopwatch::getInstance().getDelta() * 56.657223796033994f);
}