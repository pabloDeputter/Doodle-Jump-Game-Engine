//
// Created by Pablo Deputter on 21/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_COLLISION_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_COLLISION_H

#include "model/Entity.h"

#include "util/Camera.h"

namespace Utils {

class Collision
{
public:
        static bool checkCollision(const std::shared_ptr<Model::Entity>& l, const std::shared_ptr<Model::Entity>& r);
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_COLLISION_H
