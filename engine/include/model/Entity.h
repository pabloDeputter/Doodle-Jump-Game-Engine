//
// Created by Pablo Deputter on 13/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H

#include "util/Camera.h"

#include "observer/IVisitor.h"
#include "observer/Subject.h"

/**
 * @brief Namespace holds all Models
 */
namespace Model {
/**
 * @Brief Enum containing all type of Entities
 */
enum Type
{
        ePlayer = 0,
        eBonus,
        eStatic,
        eHorizontal,
        eVertical,
        eTemporary,
        eBackground,
        eJetpack,
        eSpring,
        eScore
};
/**
 * @brief Class for Entity object
 */
class Entity : public Observer::Subject, public Visitor::IVisitor
{
protected:
        float mX;         /**< X-coordinate of Entity */
        float mY;         /**< Y-coordinate of Entity */
        float mWidth;     /**< Width of Entity collision box */
        float mHeight;    /**< Height of Entity collision box */
        bool mRemoveFlag; /**< Is Entity removable */
        int mScore;       /**< Score of Entity */

public:
        /**
         * @brief Default constructor for Entity object
         *
         */
        Entity() : mX(0.f), mY(0.f), mWidth(0.f), mHeight(0.f), mRemoveFlag(false), mScore(0) {}
        /**
         * @brief Constructor for Entity object
         * @param score int - score of Entity
         */
        explicit Entity(int score) : mX(0.f), mY(0.f), mWidth(0.f), mHeight(0.f), mRemoveFlag(false), mScore(score) {}
        /**
         * @brief Destructor of Entity object
         */
        ~Entity() override { onDestroy(); }
        /**
         * @brief Get x coordinate of Entity
         * @return float - x coordinate
         */
        [[nodiscard]] float getX() const { return mX; }
        /**
         * @brief Set the x value of Entity
         * @param x float - new x coordinate
         */
        void setX(float x) { mX = x; }
        /**
         * @brief Get y coordinate of Entity
         * @return float - y coordinate
         */
        [[nodiscard]] float getY() const { return mY; }
        /**
         * @brief Set the y value of Entity
         * @param y float - new y coordinate
         */
        void setY(float y) { mY = y; }
        /**
         * @brief Get width of Entity
         * @return float - width
         */
        [[nodiscard]] float getWidth() const { return mWidth; }
        /**
         * @brief Set width of Entity
         * @param width float - new width
         */
        void setWidth(float width) { mWidth = width; }
        /**
         * @brief Get height of Entity
         * @return float - height
         */
        [[nodiscard]] float getHeight() const { return mHeight; }
        /**
         * @brief Set height of Entity
         * @param height float - new height
         */
        void setHeight(float height) { mHeight = height; }
        /**
         * @brief Get removable
         * @return flag bool
         */
        [[maybe_unused]] [[nodiscard]] bool getRemovable() const { return mRemoveFlag; }
        /**
         * @brief Set if Entity is removable
         * @param flag bool
         */
        void setRemoveFlag(bool flag) { mRemoveFlag = flag; }
        /**
         * @brief Check if Entity is removable
         * @return flag bool - true if removable
         */
        [[nodiscard]] virtual bool isRemovable() const { return mRemoveFlag; }
        /**
         * @brief Get score of Entity
         * @return int - score
         */
        [[nodiscard]] virtual int getScore() const { return mScore; }
        /**
         * @brief Set score of Entity
         * @param score int - new score
         */
        virtual void setScore(int score) { mScore = score; }
        /**
         * @brief Get type of Entity
         * @return Model::Type - type of Entity
         */
        [[nodiscard]] virtual Model::Type getType() const = 0;
        /**
         * @brief move Entity
         */
        virtual void move(bool collision) = 0;
        /**
         * @brief Move Entity object in x and y direction
         * @param x float - x value to be added to mX
         * @param y float, y value to be added to mY
         */
        void move(float x, float y)
        {
                mX += x;
                mY += y;
        }
        /**
         * @brief Set moving left
         * @param flag bool
         */
        virtual void setIsMovingLeft(bool flag) {}
        /**
         * @brief Set moving right
         * @param flag bool
         */
        virtual void setIsMovingRight(bool flag) {}
        /**
         * @brief Set moving up
         */
        virtual void setIsMovingUp(bool flag) {} // TODO
        /**
         * @brief On destroy event of Entity function will be executed
         */
        virtual void onDestroy() { Observer::Subject::clear(); }
        /**
         * @brief Check if Entity is of Type Bonus
         * @return bool - true if Bonus
         */
        [[nodiscard]] virtual bool isBonus() const { return false; }
        /**
         * @brief Check if Entity is out of view of Camera
         * @return bool - true if out of view
         */
        [[nodiscard]] bool isOutOfView() const { return mY < Utils::Camera::getInstance().getY(); }
        /**
         * @brief Visit Player object to apply Bonus
         * @param player Player - Pointer to Player
         */
        void visit(Model::Player& player) override {}
        /**
         * @brief Allow visitor to visit Entity to change state / code
         * @param visitor IVisitor - pointer to visitor who wants to visit Entity
         */
        virtual void accept(const std::shared_ptr<Visitor::IVisitor>& visitor) {}
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
