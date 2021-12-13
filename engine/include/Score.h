//
// Created by Pablo Deputter on 07/12/2021.
//

#ifndef DOODLEJUMP_SCORE_H
#define DOODLEJUMP_SCORE_H

#include "Event.h"
#include "model/Entity.h"
#include <Subject.h>

namespace Model {

class Score : public Entity, public Observer::Observer, IEventHandler
{
private:
        std::weak_ptr<Model::Entity> mLastCollision;

public:
        Score() = default;

        ~Score() override = default;

        [[nodiscard]] Model::Type getType() const override { return Model::eScore; }

        void setScore(unsigned int score) { Score::mScore += score; }

        void onTrigger(EventType type, const std::shared_ptr<Event>& event) override { event->send(*this); }

        void handleEvent(const NewMaxHeightEvent& event) override;

        void handleEvent(const CollisionEvent& event) override;

        void move(bool collision) override {}

        unsigned int getScore() const override { return mScore; }
};
} // namespace Model

#endif // DOODLEJUMP_SCORE_H
