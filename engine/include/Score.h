//
// Created by Pablo Deputter on 07/12/2021.
//

#ifndef DOODLEJUMP_SCORE_H
#define DOODLEJUMP_SCORE_H

#include <Subject.h>

class Score : public Observer::Observer
{
private:
        unsigned int mScore;

public:
        Score() : mScore(0) {}

        ~Score() override = default;

        [[nodiscard]] unsigned int getScore() const { return mScore; }

        void setScore(unsigned int score) { Score::mScore += score; }

        void onTrigger() override {}
};

#endif // DOODLEJUMP_SCORE_H
