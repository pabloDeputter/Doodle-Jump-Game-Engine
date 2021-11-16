//
// Created by Pablo Deputter on 13/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H

#include <string>

#include "../Observer/Subject.h"

/**
 * @brief Namespace holds all models
 */
namespace Model {

/**
 * @Brief Namespace contains all different entities
 */
enum Type
{
        ePlayer = 0,
        eBonus = 1,
        ePlatform = 2,
};

class Entity : public Observer::Subject
{
private:
        float mX = 0.f;
        float mY = 0.f;

public:
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

        virtual Model::Type getType() const = 0;
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
