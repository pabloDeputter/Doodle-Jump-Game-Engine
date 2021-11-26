//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYER_H

#include "Entity.h"

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

        const float mMaxVelocity = 27.f; /**< Max velocity Player can achieve */
        const float mAcceleration = 1.5; /**< Acceleration of Player */
        const float mDrag = 0.6f;        /**< Resistance applied to Player */

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

        bool isMovingUp() const;

        void setIsMovingUp(bool isMovingUp);

        bool isMovingDown() const;

        void setIsMovingDown(bool isMovingDown);

        bool isMovingLeft() const;

        void setIsMovingLeft(bool isMovingLeft);

        bool isMovingRight() const;

        void setIsMovingRight(bool isMovingRight);
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYER_H
