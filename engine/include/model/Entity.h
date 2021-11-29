//
// Created by Pablo Deputter on 13/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H

#include "Subject.h"
#include "util/Stopwatch.h"

#include <string>

/**
 * @brief Namespace holds all Models
 */
namespace Model {
/**
 * @Brief Enum containing enumerated Entities
 */
enum Type
{
        ePlayer = 0,
        eBonus = 1,
        eStatic = 2,
        eHorizontal = 3,
        eVertical = 4,
        eTemporary = 5
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
        friend Observer::Subject;
        /**
         * @brief Default constructor
         */
        Entity() = default;
        /**
         * @brief Default constructor
         */
        virtual ~Entity() = default;
        /**
         * @brief Custom constructor
         * @param x float
         * @param y float
         */
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
         * @brief Get width of Entity object
         * @return float
         */
        float getWidth() const;
        /**
         * @brief Get height of Entity object
         * @return float
         */
        float getHeight() const;
        /**
         * @brief Set width of Entity object
         * @param width float
         */
        void setWidth(float width);
        /**
         * @brief Set height of Entity object
         * @param height float
         */
        void setHeight(float height);
        /**
         * @brief move Entity object
         */
        virtual void move(bool collision) = 0;
        /**
         * @brief Move Entity object in x and y direction
         * @param x float, added to mX
         * @param y float, added to mY
         */
        void move(float x, float y);
        /**
         * @brief Get type of Entity object
         * @return Model::Type
         */
        virtual Model::Type getType() const = 0;
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H