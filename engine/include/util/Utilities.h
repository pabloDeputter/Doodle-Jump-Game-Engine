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
         * @param l Entity - pointer to first entity
         * @param r Entity - pointer to second entity
         * @return bool - true if collided
         */
        static bool checkCollision(const std::shared_ptr<Model::Entity>& l, const std::shared_ptr<Model::Entity>& r);
        /**
         * @brief Check random spawn rate of total chance
         * @param rand float - random spawn rate
         * @param weight float - total chance
         * @return true if rand <= weight
         */
        static bool checkWeight(float& rand, float weight);
        /**
         * @brief Traverse rainbow colors everytime member gets called
         * @tparam Type Object class
         * @tparam Color Color class - to change color of object
         * @param object Type - change color of this object
         */
        template <class Type, class Color>
        static void setRainbowColor(Type& object)
        {
                if (object.getFillColor().r + 5 <= 255 && object.getFillColor().g == 0 &&
                    object.getFillColor().b == 0) {
                        object.setFillColor(Color(object.getFillColor().r + 5, 0, 0));
                } else if (object.getFillColor().r == 255 && object.getFillColor().g + 5 <= 255 &&
                           object.getFillColor().b == 0) {
                        object.setFillColor(Color(255, object.getFillColor().g + 5, 0));
                } else if (object.getFillColor().r - 5 >= 0 && object.getFillColor().g == 255 &&
                           object.getFillColor().b == 0) {
                        object.setFillColor(Color(object.getFillColor().r - 5, 255, 0));
                } else if (object.getFillColor().r == 0 && object.getFillColor().g == 255 &&
                           object.getFillColor().b + 5 <= 255) {
                        object.setFillColor(Color(0, 255, object.getFillColor().b + 5));
                } else if (object.getFillColor().r == 0 && object.getFillColor().g - 5 >= 0 &&
                           object.getFillColor().b == 255) {
                        object.setFillColor(Color(0, object.getFillColor().g - 5, 255));
                } else if (object.getFillColor().r + 5 <= 255 && object.getFillColor().g == 0 &&
                           object.getFillColor().b == 255) {
                        object.setFillColor(Color(object.getFillColor().r + 5, 0, 255));
                } else if (object.getFillColor().r == 255 && object.getFillColor().g == 0 &&
                           object.getFillColor().b - 5 >= 0) {
                        object.setFillColor(Color(255, 0, object.getFillColor().b - 5));
                }
        }
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_COLLISION_H
