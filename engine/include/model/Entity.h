//
// Created by Pablo Deputter on 13/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H

#include "Subject.h"

#include "IVisitor.h"

#include <iostream>
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
        float mX; /**< X-coordinate of Entity */
        float mY; /**< Y-coordinate of Entity */
        //
        //
        float mWidth{};  /**< Width of Entity collision box */
        float mHeight{}; /**< Height of Entity collision box */
        bool mRemoveFlag;
        int mScore;

public:
        /**
         * @brief Default constructor
         */
        Entity() : mX(0.f), mY(0.f), mWidth(0.f), mHeight(0.f), mRemoveFlag(false), mScore(0) {}

        Entity(unsigned int score) : mX(0.f), mY(0.f), mWidth(0.f), mHeight(0.f), mRemoveFlag(false), mScore(score) {}

        /**
         * @brief Default constructor
         */
        virtual ~Entity() = default;
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
        [[nodiscard]] virtual Model::Type getType() const = 0;
        /**
         * @brief On destroy event of Entity function will be executed
         */
        virtual void onDestroy();

        void visit(Model::Player& player) override {}

        virtual void accept(const std::shared_ptr<Visitor::IVisitor>& visitor) {}

        void setRemoveFlag(bool flag);

        [[nodiscard]] bool getRemovable() const { return mRemoveFlag; }

        virtual bool isRemovable() const { return mRemoveFlag; }

        virtual bool isBonus() const { return false; }

        void setScore(unsigned int score) { mScore = score; }

        virtual unsigned int getScore() const { return mScore; }
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
