//
// Created by Pablo Deputter on 13/11/2021.
//

#include "model/Platform.h"

using namespace Model;

void Platform::move(bool collision)
{
        //        if (mSort == eHorizontal && ( mBoundX.first == 0 || mBoundX.second == 0) ) { initBounds(); }
        if (mSort == eVertical && (mBoundY.first == 0 || mBoundY.second == 0)) {
                initBounds();
        }

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
                break;
        case eVertical:
                std::cout << mY << " - " << mBoundY.second << "\n";
                if (mY >= mBoundY.second)
                        mMovingDown = false;
                else if (mY <= mBoundY.first)
                        mMovingDown = true;
                if (mMovingDown) {
                        Entity::move(0.f, .75f * Utils::Stopwatch::GetDelta() * 56.657223796033994f);
                } else if (!mMovingDown) {
                        Entity::move(0.f, -.75f * Utils::Stopwatch::GetDelta() * 56.657223796033994f);
                }
                break;
        case eTemporary:
                break;
        }
}

void Platform::initBounds()
{
        mBoundX = std::make_pair(mX, mX + 100.f);
        mBoundY = std::make_pair(mY, mY + 100.f);
}
