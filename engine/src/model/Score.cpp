//
// Created by Pablo Deputter on 07/12/2021.
//

#include "model/Score.h"

using namespace Model;

void Score::handleEvent(const NewMaxHeightEvent& event)
{
        float diff = event.getNewHeight() - event.getLastHeight();
        // Round up to 1 otherwise, score will not be increased
        if (diff < 1.f) {
                diff = 1.f;
        }
        // Increase score
        mScore += (int)diff;
}

void Score::handleEvent(const CollisionEvent& event)
{
        // Check if weak_ptr is still valid and is initialized
        if (mLastCollision.lock() && mLastCollision.lock() != nullptr && mLastCollision.lock() == event.getEntity()) {
                // Subtract points of object
                mScore -= event.getEntity()->getScore();
                if (mScore < 0) {
                        mScore = 0;
                }
        }
        // Add points of object to total score
        else {
                mScore += event.getEntity()->getScore();
        }
        // Assign Entity to be last seen collision
        mLastCollision = event.getEntity();
}
