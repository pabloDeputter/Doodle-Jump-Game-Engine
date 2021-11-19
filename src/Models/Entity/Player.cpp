//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Player.h"

using namespace Model;

void Player::move(float deltaTime)
{
        // Reset direction of player
        mDirection = std::make_pair(0.f, 0.f);

        // Calculate move
        if (mIsMovingUp) {
                mDirection.second = -1.f;
                if (mVelocity.second > -mMaxVelocity) {
                        mVelocity.second += mAcceleration * mDirection.second * deltaTime * 56.657223796033994f;
                }
        } else if (mIsMovingDown) {
                mDirection.second = 1.f;
                if (mVelocity.second < mMaxVelocity) {
                        mVelocity.second += mAcceleration * mDirection.second * deltaTime * 56.657223796033994f;
                }
        } else if (mIsMovingRight) {
                mDirection.first = 1.f;
                if (mVelocity.first > -mMaxVelocity) {
                        mVelocity.first += mAcceleration * mDirection.first * deltaTime * 56.657223796033994f;
                }
        } else if (mIsMovingLeft) {
                mDirection.first = -1.f;
                if (mVelocity.first < mMaxVelocity) {
                        mVelocity.first += mAcceleration * mDirection.first * deltaTime * 56.657223796033994f;
                }
        }

        // Apply drag / resistance
        if (mVelocity.first > 0.f) {

                mVelocity.first -= mDrag * deltaTime * 56.657223796033994f;
                if (mVelocity.first < 0.f) {
                        // Velocity can't be negative, just slow down
                        mVelocity.first = 0.0f;
                }
        } else if (mVelocity.first < 0.f) {

                mVelocity.first += mDrag * deltaTime * 56.657223796033994f;
                if (mVelocity.first > 0.f) {
                        // Velocity can't be negative, just slow down
                        mVelocity.first = 0.0f;
                }
        }
        if (mVelocity.second > 0.f) {
                mVelocity.second -= mDrag * deltaTime * 56.657223796033994f;
                if (mVelocity.second < 0.f) {
                        // Velocity can't be negative, just slow down
                        mVelocity.second = 0.0f;
                }
        } else if (mVelocity.second < 0.f) {
                mVelocity.second += mDrag * deltaTime * 56.657223796033994f;
                if (mVelocity.second > 0.f) {
                        // Velocity can't be negative, just slow down
                        mVelocity.second = 0.0f;
                }
        }

        // Finally move Player
        mX += mVelocity.first * deltaTime * 56.657223796033994f;
        mY += mVelocity.second * deltaTime * 56.657223796033994f;
        std::cout << "playerPosition: " << getX() << " - " << getY() << std::endl;
        notifyObserver();
}
