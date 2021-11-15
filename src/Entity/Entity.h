//
// Created by Pablo Deputter on 13/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H

#include <string>

#include "../Observer/Observable.h"

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
        eJetpack = 1,
        eSpring = 2,
        ePlatform = 3,
};

class Entity : public Observer::Observable
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
