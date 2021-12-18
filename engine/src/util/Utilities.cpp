//
// Created by Pablo Deputter on 21/11/2021.
//

#include "util/Utilities.h"

using namespace Utils;

bool Utilities::checkCollision(const std::shared_ptr<Model::Entity>& l, const std::shared_ptr<Model::Entity>& r)
{
        // We use basic rectangles to check collisions between entities and create these so that the position of
        // the model is the center of the collision rectangle.
        if (l->getX() - (l->getWidth() / 2.f) + l->getWidth() >=
                r->getX() - (r->getWidth() / 2.f) && // l right edge is past r left edge
            l->getX() - (l->getWidth() / 2.f) <=
                r->getX() - (r->getWidth() / 2.f) + r->getWidth() && // l left edge is past r right edge
            l->getY() + l->getHeight() >= r->getY() &&  // l top edge is past r bottom edge
            l->getY() <= r->getY() + r->getHeight())                 // l bottom edge is past r top edge
        {
                return true;
        }
        return false;
}

bool Utilities::checkWeight(float& rand, float weight)
{
        // If rand <= weight, return true
        if (rand <= weight) {
                return true;
        }
        // If not subtract weight from rand and function will get called again
        rand -= weight;
        return false;
}