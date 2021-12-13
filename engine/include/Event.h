//
// Created by Pablo Deputter on 08/12/2021.
//

#ifndef DOODLEJUMP_EVENT_H
#define DOODLEJUMP_EVENT_H

#include "Settings.h"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace Model {
class Entity;
class Player;
} // namespace Model

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

class Event;
class DrawEvent;
class OutOfViewEvent;
class NewMaxHeightEvent;
class CollisionEvent;
class KeyPressedEvent;
class MoveEvent;
class StopBonusEvent;
class NewDifficultyEvent;

class IEventHandler
{
public:
        virtual void handleEvent(const Event& event) {}

        virtual void handleEvent(const DrawEvent& event) {}

        virtual void handleEvent(const OutOfViewEvent& event) {}

        virtual void handleEvent(const NewMaxHeightEvent& event) {}

        virtual void handleEvent(const CollisionEvent& event) {}

        virtual void handleEvent(const KeyPressedEvent& event) {}

        virtual void handleEvent(const MoveEvent& event) {}

        virtual void handleEvent(const StopBonusEvent& event) {}

        virtual void handleEvent(const NewDifficultyEvent& event) {}
};

class Event
{
protected:
        EventType mEvent;

public:
        explicit Event(EventType mEvent) : mEvent(mEvent) {}

        Event() = default;

        virtual ~Event() = default;

        virtual void send(IEventHandler& handler) const { handler.handleEvent(*this); }

        [[nodiscard]] EventType getEvent() const { return mEvent; }
};

class DrawEvent : public Event
{
public:
        DrawEvent() : Event() {}

        ~DrawEvent() override = default;

        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }
};

class OutOfViewEvent : public Event
{
public:
        OutOfViewEvent() : Event() {}

        ~OutOfViewEvent() override = default;

        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }
};

class NewMaxHeightEvent : public Event
{
private:
        float mLastHeight;
        float mNewHeight;

public:
        NewMaxHeightEvent(float lastHeight, float newHeight) : Event(), mLastHeight(lastHeight), mNewHeight(newHeight)
        {
        }

        ~NewMaxHeightEvent() override = default;

        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }

        float getLastHeight() const { return mLastHeight; }

        float getNewHeight() const { return mNewHeight; }
};

class CollisionEvent : public Event
{
private:
        std::shared_ptr<Model::Entity> mEntity;
        std::shared_ptr<Model::Player> mPlayer;

public:
        explicit CollisionEvent(std::shared_ptr<Model::Entity> entity, std::shared_ptr<Model::Player> player)
            : Event(), mEntity(std::move(entity)), mPlayer(std::move(player))
        {
        }

        ~CollisionEvent() override = default;

        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }

        const std::shared_ptr<Model::Entity>& getEntity() const { return mEntity; }

        const std::shared_ptr<Model::Player>& getPlayer() const { return mPlayer; }
};

class KeyPressedEvent : public Event
{
private:
        std::string mKey;
        bool mIsPressed;

public:
        KeyPressedEvent(std::string key, bool isPressed) : Event(), mKey(std::move(key)), mIsPressed(isPressed) {}

        ~KeyPressedEvent() override = default;

        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }

        const std::string& getKey() const { return mKey; }

        bool isPressed() const { return mIsPressed; }
};

class MoveEvent : public Event
{
private:
        bool mCollided;

public:
        explicit MoveEvent(bool collided) : Event(), mCollided(collided) {}

        ~MoveEvent() override = default;

        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }

        bool isCollided() const { return mCollided; }
};

class StopBonusEvent : public Event
{
private:
        std::shared_ptr<Model::Entity> mBonus;

public:
        explicit StopBonusEvent(std::shared_ptr<Model::Entity> bonus) : Event(), mBonus(std::move(bonus)) {}

        ~StopBonusEvent() override = default;

        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }

        const std::shared_ptr<Model::Entity>& getBonus() const { return mBonus; }
};

class NewDifficultyEvent : public Event
{
private:
        Settings::Difficulty mDifficulty;

public:
        explicit NewDifficultyEvent(Settings::Difficulty difficulty) : Event(), mDifficulty(difficulty) {}

        ~NewDifficultyEvent() override = default;

        void send(IEventHandler& handler) const override { handler.handleEvent(*this); }

        [[nodiscard]] Settings::Difficulty getDifficulty() const { return mDifficulty; }
};

#endif // DOODLEJUMP_EVENT_H
