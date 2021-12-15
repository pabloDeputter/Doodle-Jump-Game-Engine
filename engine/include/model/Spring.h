//
// Created by Pablo Deputter on 06/12/2021.
//

#ifndef DOODLEJUMP_SPRING_H
#define DOODLEJUMP_SPRING_H

#include "Bonus.h"
#include "Player.h"
#include <cmath>

namespace Model {

class Spring : public Bonus
{
private:
        void visit(Model::Player& player) override;

public:
        Spring(unsigned int score, float spawnRate, bool started) : Bonus(score, spawnRate, started){};

        Spring() : Bonus(15, .75){};

        ~Spring() override = default;

        [[nodiscard]] Model::Type getType() const override { return Model::eSpring; }

        [[nodiscard]] bool isRemovable() const override { return mRemoveFlag; }
};
} // namespace Model

#endif // DOODLEJUMP_SPRING_H
