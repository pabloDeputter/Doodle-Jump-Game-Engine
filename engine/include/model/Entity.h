//
// Created by Pablo Deputter on 13/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H

#include "Subject.h"
#include "util/Camera.h"
#include "util/Stopwatch.h"

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
        eBonus = 1,
        eStatic = 2,
        eHorizontal = 3,
        eVertical = 4,
        eTemporary = 5,
        eBackground = 6,
        eJetpack = 7,
        eSpring = 8,
        eScore = 9
};

class CollisionBox
{
private:
        float mLeft;
        float mWidth;
        float mBottom;
        float mHeight;

public:
        CollisionBox() = default;

        CollisionBox(float left, float width, float bottom, float height)
            : mLeft(left), mWidth(width), mBottom(bottom), mHeight(height)
        {
        }

        ~CollisionBox() = default;

        [[nodiscard]] float getLeft() const { return mLeft; }

        [[nodiscard]] float getWidth() const { return mWidth; }

        [[nodiscard]] float getBottom() const { return mBottom; }

        [[nodiscard]] float getHeight() const { return mHeight; }
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
        unsigned int mScore;

        float mSpawnRate;

public:
        /**
         * @brief Default constructor
         */
        Entity() = default;

        explicit Entity(float spawnRate)
            : mX(0.f), mY(0.f), mWidth(0.f), mHeight(0.f), mRemoveFlag(false), mScore(0.f), mSpawnRate(spawnRate)
        {
        }

        /**
         * @brief Default constructor
         */
        virtual ~Entity() = default;
        /**
         * @brief Custom constructor
         * @param x float
         * @param y float
         */
        Entity(float x, float y) : mX(x), mY(y), mRemoveFlag(false) {}
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
        virtual Model::Type getType() const = 0;
        /**
         * @brief On destroy event of Entity function will be executed
         */
        virtual void onDestroy();

        void visit(Model::Player& player) override { std::cout << "Entity visit\n"; }

        virtual void accept(const std::shared_ptr<Visitor::IVisitor>& visitor) {}

        // TODO - jetpack
        void setRemoveFlag(bool flag)
        {
                mRemoveFlag = flag;
                onDestroy();
        }

        virtual bool getRemovable() const { return mRemoveFlag; }

        virtual bool isRemovable() const { return mRemoveFlag; }

        virtual bool isBonus() const { return false; }

        void setScore(unsigned int score) { mScore = score; }

        virtual unsigned int getScore() const { return mScore; }

        virtual float getSpawnRate() const { return mSpawnRate; }

        void setSpawnRate(float spawnRate) { mSpawnRate = spawnRate; }
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
