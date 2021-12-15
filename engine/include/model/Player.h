//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYER_H

#include "Entity.h"
#include "observer/IVisitor.h"

/**
 * @brief Namespace holds all Models
 */
namespace Model {
/**
 * @brief Class for Player object
 */
class Player : public Entity, public Observer::Observer, public IEventHandler
{
public:
        /**
         * @brief Player state
         */
        enum PlayerState
        {
                eNormal = 0,
                eFlying
        };

private:
        std::pair<float, float> mVelocity;  /**< Current velocity of Player */
        std::pair<float, float> mDirection; /**< Current direction of Player */
        const float mMaxVelocity = 0.20f;   /**< Max velocity Player can achieve */
        const float mAcceleration = 0.015f; /**< Acceleration of Player */
        float mDrag = 0.005f;               /**< Resistance applied to Player */

        bool mIsMovingLeft;  /**< Player is moving left */
        bool mIsMovingRight; /**< Player is moving right */
        bool mState;         /**< State Player is currently in */

private:
        /**
         * @brief On trigger of Subject
         * @param type EventType - type of event
         * @param event Event - Pointer to event
         */
        void onTrigger(EventType type, const std::shared_ptr<Event>& event) override { event->send(*this); }
        /**
         * @brief Allow visitor to visit Player to change state / code
         * @param visitor IVisitor - pointer to visitor who wants to visit Player
         */
        void accept(const std::shared_ptr<Visitor::IVisitor>& visitor) override { visitor->visit(*this); }
        /**
         * @brief Handle StopBonusEvent
         * @param event StopBonusEvent
         */
        void handleEvent(const StopBonusEvent& event) override { accept(event.getBonus()); }

public:
        /**
         * @brief Constructor for Player object
         */
        Player()
            : mVelocity({0.f, 0.f}), mDirection({0.f, 0.f}), mIsMovingLeft(false), mIsMovingRight(false),
              mState(eNormal)
        {
        }
        /**
         * @brief Default destructor for Player object
         */
        ~Player() override = default;
        /**
         * @brief Get type of Player
         * @return Model::Type - type of Player
         */
        [[nodiscard]] Model::Type getType() const override { return Model::ePlayer; }
        /**
         * @brief Move
         * @param collision bool - collided or not
         */
        void move(bool collision) override;
        /**
         * @brief Get velocity
         * @return std::pair<float,float> - current velocity of Player
         */
        [[nodiscard]] const std::pair<float, float>& getVelocity() const { return mVelocity; }
        /**
         * @brief Set velocity
         * @param velocity std::pair<float,float> - new velocity of Player
         */
        void setVelocity(const std::pair<float, float>& velocity) { mVelocity = velocity; }
        /**
         * @brief Get direction
         * @return std::pair<float, float> - current direction of Player
         */
        [[maybe_unused]] [[nodiscard]] const std::pair<float, float>& getDirection() const { return mDirection; }
        /**
         * @brief Set direction
         * @param direction std::pair<float,float> - new direction of Player
         */
        [[maybe_unused]] void setDirection(const std::pair<float, float>& direction) { mDirection = direction; }
        /**
         * @brief Get max velocity
         * @return float
         */
        [[nodiscard]] float getMaxVelocity() const { return mMaxVelocity; }
        /**
         * @brief Get acceleration
         * @return float
         */
        [[maybe_unused]] [[nodiscard]] float getAcceleration() const { return mAcceleration; }
        /**
         * @brief Get drag
         * @return float
         */
        [[nodiscard]] float getDrag() const { return mDrag; }
        /**
         * @brief Set drag
         * @param drag float - new drag of Player
         */
        void setDrag(float drag) { mDrag = drag; }
        /**
         * @brief Set moving left
         * @param flag bool
         */
        void setIsMovingLeft(bool flag) override { mIsMovingLeft = flag; }
        /**
         * @brief Set moving right
         * @param flag bool
         */
        void setIsMovingRight(bool flag) override { mIsMovingRight = flag; }
        /**
         * @brief Set state of Player
         * @param state PlayerState - new state of Player
         */
        void setState(PlayerState state) { mState = state; }
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYER_H
