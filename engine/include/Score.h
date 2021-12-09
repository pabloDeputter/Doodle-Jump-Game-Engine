//
// Created by Pablo Deputter on 07/12/2021.
//

#ifndef DOODLEJUMP_SCORE_H
#define DOODLEJUMP_SCORE_H

#include "Event.h"
#include "model/Entity.h"
#include <Subject.h>

class Score : public Observer::Observer, public IEventHandler
{
private:
        unsigned int mScore;

public:
        Score() : mScore(0) {}

        ~Score() override = default;

        [[nodiscard]] unsigned int getScore() const { return mScore; }

        void setScore(unsigned int score) { Score::mScore += score; }

        void onTrigger(EventType type, const std::shared_ptr<Event>& event) override { event->send(*this); }

        void handleEvent(const NewMaxHeightEvent& event) override;

        void handleEvent(const CollisionEvent& event) override;
};

#endif // DOODLEJUMP_SCORE_H
