//
// Created by Pablo Deputter on 06/12/2021.
//

#ifndef DOODLEJUMP_JETPACK_H
#define DOODLEJUMP_JETPACK_H

#include "Bonus.h"
#include "Player.h"

namespace Model {

class Jetpack : public Bonus
{
private:
        void visit(Model::Player& player) override;

public:
        Jetpack(unsigned int score, float spawnRate, bool started) : Bonus(score, spawnRate, started) {}

        Jetpack() : Bonus(25, .2) {}

        explicit Jetpack(bool started) : Bonus(started) {}

        ~Jetpack() override = default;

        [[nodiscard]] Model::Type getType() const override { return Model::eJetpack; }

        [[nodiscard]] bool isRemovable() const override;
};
} // namespace Model

#endif // DOODLEJUMP_JETPACK_H
