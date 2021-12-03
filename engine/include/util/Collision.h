//
// Created by Pablo Deputter on 21/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_COLLISION_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_COLLISION_H

#include "model/Entity.h"

#include "util/Camera.h"

/**
 * @brief Namespace holds all Utilities
 */
namespace Utils {
/**
 * @brief Class for Collisions
 */
class Collision
{
public:
        /**
         * @brief Check if there is a collision between two Entities
         * @param l first entity
         * @param r second entity
         * @return bool
         */
        static bool checkCollision(const std::shared_ptr<Model::Entity>& l, const std::shared_ptr<Model::Entity>& r);
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_COLLISION_H
