//
// Created by Pablo Deputter on 13/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H

#include "../../Observer/Subject.h"

#include <string>

/**
 * @brief Namespace holds all models
 */
namespace Model {

/**
 * @Brief Enum containing enumerated Entities
 */
enum Type
{
        ePlayer = 0,
        eBonus = 1,
        ePlatform = 2,
};

/**
 * @brief Class for Entity object
 */
class Entity : public Observer::Subject
{
protected:
        float mX;        /**< X-coordinate of Entity */
        float mY;        /**< Y-coordinate of Entity */
        float mWidth{};  /**< Width of Entity collision box */
        float mHeight{}; /**< Height of Entity collision box */

public:
        Entity() = default;

        virtual ~Entity() = default;

        Entity(float x, float y) : mX(x), mY(y) {}

        /**
         * @brief Get the x value of Entity object
         * @return float
         */
        float getX() const;
        /**
         * @brief Get the y value of Entity object
         * @return float
         */
        float getY() const;
        /**
         * @brief Set the x value of Entity object
         * @param x float
         */
        void setX(float x);
        /**
         * @brief Set the y value of Entity object
         * @param y float
         */
        void setY(float y);
        /**
         * @brief Get type of Entity object
         * @return Model::Type
         */
        virtual Model::Type getType() const = 0;
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
