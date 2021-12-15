//
// Created by Pablo Deputter on 07/12/2021.
//

#ifndef DOODLEJUMP_SCORE_H
#define DOODLEJUMP_SCORE_H

#include "model/Entity.h"

#include "Event.h"

#include "Subject.h"

/**
 * @brief Namespace holds Models
 */
namespace Model {
/**
 * @brief Class for Score of Game
 */
class Score : public Entity, public Observer::Observer, public IEventHandler
{
private:
        std::weak_ptr<Model::Entity> mLastCollision; /**< Pointer to last Entity Player has collided with */

private:
        /**
         * @brief On trigger of Subject
         * @param type EventType - type of event
         * @param event Event - Pointer to event
         */
        void onTrigger(EventType type, const std::shared_ptr<Event>& event) override { event->send(*this); }
        /**
         * @brief Handle NewMaxHeightEvent
         * @param event NewMaxHeightEvent
         */
        void handleEvent(const NewMaxHeightEvent& event) override;
        /**
         * Handle CollisionEvent
         * @param event CollisionEvent
         */
        void handleEvent(const CollisionEvent& event) override;

public:
        /**
         * @brief Default constructor for Score object
         */
        Score() = default;
        /**
         * @brief Default destructor for Score object
         */
        ~Score() override = default;
        /**
         * @brief Get type of Score
         * @return Model::Type - type of Score
         */
        [[nodiscard]] Model::Type getType() const override { return Model::eScore; }
        /**
         * @brief Move Score
         * @param collision bool - collided ot not
         */
        void move(bool collision) override {}
        /**
         * @brief Get score
         * @return int - score
         */
        [[nodiscard]] int getScore() const override { return mScore; }
        /**
         * @brief Add to score
         * @param score int - score to be added
         */
        void setScore(int score) override { Score::mScore += score; }
};
} // namespace Model

#endif // DOODLEJUMP_SCORE_H
