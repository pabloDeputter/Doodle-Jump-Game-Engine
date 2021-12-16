//
// Created by Pablo Deputter on 08/12/2021.
//

#ifndef DOODLEJUMP_EVENTS_H
#define DOODLEJUMP_EVENTS_H

#include "Settings.h"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

// Forward declaration
namespace Model {
class Entity;
class Player;
} // namespace Model

/**
 * @brief Enum holds all different Event types
 */
enum class EventType
{
        OUT_OF_VIEW = 0,
        DRAW,
        NEW_MAX_HEIGHT,
        COLLISION,
        KEY_PRESSED,
        MOVE,
        STOP_BONUS,
        NEW_DIFFICULTY
};

// Forward declaration of different Event
class Event;
class DrawEvent;
class OutOfViewEvent;
class NewMaxHeightEvent;
class CollisionEvent;
class KeyPressedEvent;
class MoveEvent;
class StopBonusEvent;
class NewDifficultyEvent;

/**
 * @brief Abstract IEventHandler class
 */
class IEventHandler
{
public:
        /**
         * @brief Handle abstract Event
         * @param event Event - event to be handled
         */
        virtual void handleEvent(const Event& event) {}

        /**
         * @brief Handle DrawEvent Event
         * @param event DrawEvent - event to be handled
         */
        virtual void handleEvent(const DrawEvent& event) {}
        /**
         * @brief Handle OutOfViewEvent Event
         * @param event OutOfViewEvent - event to be handled
         */
        virtual void handleEvent(const OutOfViewEvent& event) {}
        /**
         * @brief Handle NewMaxHeightEvent Event
         * @param event NewMaxHeightEvent - event to be handled
         */
        virtual void handleEvent(const NewMaxHeightEvent& event) {}
        /**
         * @brief Handle CollisionEvent Event
         * @param event CollisionEvent - event to be handled
         */
        virtual void handleEvent(const CollisionEvent& event) {}
        /**
         * @brief Handle KeyPressedEvent Event
         * @param event KeyPressedEvent - event to be handled
         */
        virtual void handleEvent(const KeyPressedEvent& event) {}
        /**
         * @brief Handle MoveEvent Event
         * @param event MoveEvent - event to be handled
         */
        virtual void handleEvent(const MoveEvent& event) {}
        /**
         * @brief Handle StopBonusEvent Event
         * @param event StopBonusEvent - event to be handled
         */
        virtual void handleEvent(const StopBonusEvent& event) {}
        /**
         * @brief Handle NewDifficultyEvent Event
         * @param event NewDifficultyEvent - event to be handled
         */
        virtual void handleEvent(const NewDifficultyEvent& event) {}
};

/**
 * @brief Abstract Event class
 */
class Event
{
protected:
        EventType mEvent; /**< Type of event */

public:
        /**
         * Constructor for Event object
         * @param mEvent EventType - type of event
         */
        explicit Event(EventType mEvent) : mEvent(mEvent) {}
        /**
         * Default destructor for Event object
         */
        virtual ~Event() = default;
        /**
         * @brief Send event to IEvent handler to correctly handle event
         * @param handler IEventHandler - abstract event handler
         */
        virtual void send(IEventHandler& handler) const { handler.handleEvent(*this); }
        /**
         * @brief Get type of event
         * @return EventType - type of event
         */
        [[maybe_unused]] [[nodiscard]] EventType getEvent() const { return mEvent; }
};

/**
 * @brief Class for when object needs to be drawn
 */
class DrawEvent : public Event
{
private:
        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }

public:
        /**
         * @brief Constructor for DrawEvent
         */
        DrawEvent() : Event(EventType::DRAW) {}
        ~DrawEvent() override = default;
};

/**
 * @brief Class for when object gets out of view of Camera
 */
class OutOfViewEvent : public Event
{
private:
        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }

public:
        /**
         * @brief Constructor for OutOfViewEvent
         */
        OutOfViewEvent() : Event(EventType::OUT_OF_VIEW) {}
        ~OutOfViewEvent() override = default;
};

/**
 * @brief Class for when Camera / achieves a new height
 */
class NewMaxHeightEvent : public Event
{
private:
        float mLastHeight; /**< Last max. height */
        float mNewHeight;  /**< new max/ height */
private:
        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }

public:
        /**
         * @brief Constructor for NewMaxHeightEvent object
         * @param lastHeight float - last max. height
         * @param newHeight float - new max. height
         */
        NewMaxHeightEvent(float lastHeight, float newHeight)
            : Event(EventType::NEW_MAX_HEIGHT), mLastHeight(lastHeight), mNewHeight(newHeight)
        {
        }
        ~NewMaxHeightEvent() override = default;
        /**
         * @brief Get last max. height
         * @return float - last max. height
         */
        [[nodiscard]] float getLastHeight() const { return mLastHeight; }
        /**
         * @brief Get new max. height
         * @return float - new max. height
         */
        [[nodiscard]] float getNewHeight() const { return mNewHeight; }
};

/**
 * @brief Class for when Entity collides with other Player
 */
class CollisionEvent : public Event
{
private:
        std::shared_ptr<Model::Entity> mEntity; /**< Pointer to Entity */
        std::shared_ptr<Model::Player> mPlayer; /**< Pointer to Player */
private:
        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }

public:
        /**
         * @brief Constructor for CollisionEvent object
         * @param entity Model::Entity - pointer to Entity
         * @param player Model::Player - pointer to Player
         */
        explicit CollisionEvent(std::shared_ptr<Model::Entity> entity, std::shared_ptr<Model::Player> player)
            : Event(EventType::COLLISION), mEntity(std::move(entity)), mPlayer(std::move(player))
        {
        }
        ~CollisionEvent() override = default;
        /**
         * @brief Get Entity
         * @return Model::Entity - pointer to Entity
         */
        [[nodiscard]] const std::shared_ptr<Model::Entity>& getEntity() const { return mEntity; }
        /**
         * @brief Get Player
         * @return Model::Player - pointer to Player
         */
        [[nodiscard]] const std::shared_ptr<Model::Player>& getPlayer() const { return mPlayer; }
};

/**
 * @brief Class for when key is pressed
 */
class KeyPressedEvent : public Event
{
private:
        std::string mKey; /**< Key pressed in std::string form */
        bool mIsPressed;  /**< Is key pressed */
private:
        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }

public:
        /**
         * @brief Constructor for KeyPressedEvent object
         * @param key std::string - key pressed
         * @param isPressed bool - is key pressed
         */
        KeyPressedEvent(std::string key, bool isPressed)
            : Event(EventType::KEY_PRESSED), mKey(std::move(key)), mIsPressed(isPressed)
        {
        }
        ~KeyPressedEvent() override = default;
        /**
         * brief Get key
         * @return std::string - key pressed
         */
        [[nodiscard]] const std::string& getKey() const { return mKey; }
        /**
         * @brief Is key pressed
         * @return bool - is key pressed
         */
        [[nodiscard]] bool isPressed() const { return mIsPressed; }
};

/**
 * @brief Class for when Entity is moved
 */
class MoveEvent : public Event
{
private:
        bool mCollided; /**< Is entity collided */
private:
        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }

public:
        /**
         * @brief Constructor for MoveEvent object
         * @param collided bool
         */
        explicit MoveEvent(bool collided) : Event(EventType::MOVE), mCollided(collided) {}
        ~MoveEvent() override = default;
        /**
         * @brief Is collided with other Entity
         * @return bool - true if collided
         */
        [[nodiscard]] bool isCollided() const { return mCollided; }
};

/**
 * @brief Class for when Bonus has expired
 */
class StopBonusEvent : public Event
{
private:
        std::shared_ptr<Model::Entity> mBonus; /**< Pointer to Bonus */
private:
        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }

public:
        /**
         * @brief Constructor for StopBonusEvent
         * @param bonus Model::Entity - pointer to Bonus
         */
        explicit StopBonusEvent(std::shared_ptr<Model::Entity> bonus)
            : Event(EventType::STOP_BONUS), mBonus(std::move(bonus))
        {
        }
        ~StopBonusEvent() override = default;
        /**
         * @brief Get bonus
         * @return Model::Entity - pointer to Bonus
         */
        [[nodiscard]] const std::shared_ptr<Model::Entity>& getBonus() const { return mBonus; }
};

/**
 * @brief Class for when Player has achieved new difficulty
 */
class NewDifficultyEvent : public Event
{
private:
        Settings::Difficulty mDifficulty;

private:
        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }

public:
        /**
         * @brief Constructor for NewDifficultyEvent
         * @param difficulty Settings::Difficulty - newly achieved difficulty
         */
        explicit NewDifficultyEvent(Settings::Difficulty difficulty)
            : Event(EventType::NEW_DIFFICULTY), mDifficulty(difficulty)
        {
        }
        ~NewDifficultyEvent() override = default;
        /**
         * @brief Get difficulty
         * @return Settings::Difficulty - newly achieved difficulty
         */
        [[nodiscard]] Settings::Difficulty getDifficulty() const { return mDifficulty; }
};

#endif // DOODLEJUMP_EVENTS_H
