//
// Created by Pablo Deputter on 07/12/2021.
//

#include "Score.h"

using namespace Model;

void Score::handleEvent(const NewMaxHeightEvent& event)
{
        mScore += (unsigned int)(event.getNewHeight() - event.getLastHeight());
}

void Score::handleEvent(const CollisionEvent& event) { mScore += event.getEntity()->getScore(); }