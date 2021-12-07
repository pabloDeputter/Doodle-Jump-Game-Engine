//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYER_H

#include "Entity.h"
#include "IVisitor.h"
#include <iostream>

/**
 * @brief Namespace holds all model
 */
namespace Model {
/**
 * @brief Class for Player object, derives from Entity
 */
class Player : public Entity
{
private:
        std::pair<float, float> mVelocity;  /**< Current velocity of Player */
        std::pair<float, float> mDirection; /**< Current direction of Player */

        const float mMaxVelocity = 0.25f;   /**< Max velocity Player can achieve */
        const float mAcceleration = 0.015f; /**< Acceleration of Player */
        float mDrag = 0.006f;               /**< Resistance applied to Player */

        bool mIsMovingUp;    /**< Player is moving up */
        bool mIsMovingDown;  /**< Player is moving down */
        bool mIsMovingLeft;  /**< Player is moving left */
        bool mIsMovingRight; /**< Player is moving right */

public:
        Player() = default;

        ~Player() override = default;

        Model::Type getType() const override { return Model::Type::ePlayer; }

        void move(bool collision) override;

        const std::pair<float, float>& getVelocity() const;

        void setVelocity(const std::pair<float, float>& velocity);

        const std::pair<float, float>& getDirection() const;

        void setDirection(const std::pair<float, float>& direction);

        const float getMaxVelocity() const;

        const float getMaxAcceleration() const;

        const float getDrag() const;

        void setDrag(float drag);

        bool isMovingUp() const;

        void setIsMovingUp(bool isMovingUp);

        bool isMovingDown() const;

        void setIsMovingDown(bool isMovingDown);

        bool isMovingLeft() const;

        void setIsMovingLeft(bool isMovingLeft);

        bool isMovingRight() const;

        void setIsMovingRight(bool isMovingRight);

        // TODO - visitor pattern
        void accept(const std::shared_ptr<Visitor::IVisitor>& visitor) override
        {
                visitor->visit(*this);
        }
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYER_H
