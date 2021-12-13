//
// Created by Pablo Deputter on 21/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_COLLISION_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_COLLISION_H

#include "model/Entity.h"

#include <cmath>

/**
 * @brief Namespace holds all Utilities
 */
namespace Utils {
/**
 * @brief Class for Utilities
 */
class Utilities
{
public:
        /**
         * @brief Check if there is a collision between two Entities
         * @param l first entity
         * @param r second entity
         * @return bool
         */
        static bool checkCollision(const std::shared_ptr<Model::Entity>& l, const std::shared_ptr<Model::Entity>& r);
        /**
         * @brief Check random spawn rate of total chance
         * @param rand float - random spawn rate
         * @param weight float - total chance
         * @return true if rand <= weight
         */
        static bool checkWeight(float& rand, float weight);
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_COLLISION_H
