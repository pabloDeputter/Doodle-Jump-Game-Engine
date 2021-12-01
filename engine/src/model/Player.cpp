//
// Created by Pablo Deputter on 14/11/2021.
//

#include "model/Player.h"

using namespace Model;

void Player::move(bool collision)
{
        // Reset direction of player
        mDirection = std::make_pair(0.f, 0.f);

        // Calculate move
        //        if (mIsMovingUp) {
        //                mDirection.second = -1.f;
        //                if (mVelocity.second > -mMaxVelocity) {
        //                        mVelocity.second += mAcceleration * mDirection.second * Utils::Stopwatch::GetDelta()
        //                        * 56.657223796033994f;
        //                }
        //        } else if (mIsMovingDown) {
        //                mDirection.second = 1.f;
        //                if (mVelocity.second < mMaxVelocity) {
        //                        mVelocity.second += mAcceleration * mDirection.second * Utils::Stopwatch::GetDelta()
        //                        * 56.657223796033994f;
        //                }
        //         }

        if (collision) {
                mDirection.second = -1.f;
                //                mVelocity.second *= -1.f;

                mVelocity.second = -1.f * mMaxVelocity;

                //                if (mVelocity.second > -mMaxVelocity) {
                //                        mVelocity.second += mAcceleration * mDirection.second *
                //                        Utils::Stopwatch::GetDelta() *
                //                                            56.657223796033994f;
                //                }
        }

        if (mVelocity.second >= 0) {
                mDirection.second = 1.f;

                if (mVelocity.second < mMaxVelocity) {
                        mVelocity.second +=
                            mAcceleration * mDirection.second * Utils::Stopwatch::GetDelta() * 56.657223796033994f;
                }
        }

        if (mIsMovingRight) {
                mDirection.first = 1.f;
                if (mVelocity.first > -mMaxVelocity) {
                        mVelocity.first +=
                            mAcceleration * mDirection.first * Utils::Stopwatch::GetDelta() * 56.657223796033994f;
                }
        } else if (mIsMovingLeft) {
                mDirection.first = -1.f;
                if (mVelocity.first < mMaxVelocity) {
                        mVelocity.first +=
                            mAcceleration * mDirection.first * Utils::Stopwatch::GetDelta() * 56.657223796033994f;
                }
        }

        // Apply drag / resistance
        if (mVelocity.first > 0.f) {

                mVelocity.first -= mDrag * Utils::Stopwatch::GetDelta() * 56.657223796033994f;
                if (mVelocity.first < 0.f) {
                        // Velocity can't be negative, just slow down
                        mVelocity.first = 0.0f;
                }
        } else if (mVelocity.first < 0.f) {

                mVelocity.first += mDrag * Utils::Stopwatch::GetDelta() * 56.657223796033994f;
                if (mVelocity.first > 0.f) {
                        // Velocity can't be negative, just slow down
                        mVelocity.first = 0.0f;
                }
        }
        if (mVelocity.second > 0.f) {
                mVelocity.second -= mDrag * Utils::Stopwatch::GetDelta() * 56.657223796033994f;
                if (mVelocity.second < 0.f) {
                        // Velocity can't be negative, just slow down
                        mVelocity.second = 0.0f;
                }
        } else if (mVelocity.second < 0.f) {
                mVelocity.second += mDrag * Utils::Stopwatch::GetDelta() * 56.657223796033994f;
                if (mVelocity.second > 0.f) {
                        // Velocity can't be negative, just slow down
                        mVelocity.second = 0.0f;
                }
        }

        // Finally, move Player
        Entity::move(mVelocity.first * Utils::Stopwatch::GetDelta() * 56.657223796033994f,
                     mVelocity.second * Utils::Stopwatch::GetDelta() * 56.657223796033994f);
}

const std::pair<float, float>& Player::getVelocity() const { return mVelocity; }

void Player::setVelocity(const std::pair<float, float>& velocity) { Player::mVelocity = velocity; }

const std::pair<float, float>& Player::getDirection() const { return mDirection; }

void Player::setDirection(const std::pair<float, float>& direction) { Player::mDirection = direction; }

const float Player::getMaxVelocity() const { return mMaxVelocity; }

const float Player::getMaxAcceleration() const { return mAcceleration; }

const float Player::getDrag() const { return mDrag; }

bool Player::isMovingUp() const { return mIsMovingUp; }

void Player::setIsMovingUp(bool isMovingUp) { Player::mIsMovingUp = isMovingUp; }

bool Player::isMovingDown() const { return mIsMovingDown; }

void Player::setIsMovingDown(bool isMovingDown) { Player::mIsMovingDown = isMovingDown; }

bool Player::isMovingLeft() const { return mIsMovingLeft; }

void Player::setIsMovingLeft(bool isMovingLeft) { Player::mIsMovingLeft = isMovingLeft; }

bool Player::isMovingRight() const { return mIsMovingRight; }

void Player::setIsMovingRight(bool isMovingRight) { Player::mIsMovingRight = isMovingRight; }
