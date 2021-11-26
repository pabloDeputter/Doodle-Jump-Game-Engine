//
// Created by Pablo Deputter on 13/11/2021.
//

#include "model/Platform.h"

using namespace Model;

void Platform::move(bool collision)
{
        if (mBoundX.first == 0 && mBoundX.second == 0)
                initBounds();
        if (mBoundY.first == 0 && mBoundY.second == 0)
                initBounds();

        switch (mSort) {

        case eStatic:
                break;
        case eHorizontal:
                if (mX >= mBoundX.second)
                        mMovingForward = false;
                else if (mX <= mBoundX.first)
                        mMovingForward = true;
                if (mMovingForward) {
                        Entity::move(.75f * Utils::Stopwatch::GetDelta() * 56.657223796033994f, 0.f);
                } else if (!mMovingForward) {
                        Entity::move(-.75f * Utils::Stopwatch::GetDelta() * 56.657223796033994f, 0.f);
                }
        case eVertical:
                if (mY >= mBoundX.second)
                        mMovingDown = false;
                else if (mY <= mBoundX.first)
                        mMovingDown = true;
                if (mMovingDown) {
                        Entity::move(0.f, .75f * Utils::Stopwatch::GetDelta() * 56.657223796033994f);
                } else if (!mMovingDown) {
                        Entity::move(0.f, -.75f * Utils::Stopwatch::GetDelta() * 56.657223796033994f);
                }
        case eTemporary:
                break;
        }
}

void Platform::initBounds()
{
        mBoundX = std::make_pair(mX - 50.F, mX + 50.f);
        mBoundY = std::make_pair(mY - 50.f, mY + 50.f);
}

Platform::Sort Platform::getSort() const { return mSort; }

void Platform::setSort(Platform::Sort sort) { mSort = sort; }
