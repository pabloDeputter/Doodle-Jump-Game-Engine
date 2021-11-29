//
// Created by Pablo Deputter on 21/11/2021.
//

#include "util/Collision.h"

using namespace Utils;
#include <iostream>
bool Collision::checkCollision(const std::shared_ptr<Model::Entity>& l, const std::shared_ptr<Model::Entity>& r)
{
        if (l->getX() + l->getWidth() >= r->getX() &&  // l right edge is past r left edge
            l->getX() <= r->getX() + r->getWidth() &&  // l left edge is past r right edge
            l->getY() + l->getHeight() >= r->getY() && // l top edge is past r bottom edge
            l->getY() <= r->getY() + r->getHeight())   // l bottom edge is past r top edge
        {
                return true;
        }

        return false;
}
