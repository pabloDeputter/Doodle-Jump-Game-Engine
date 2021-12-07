//
// Created by Pablo Deputter on 06/12/2021.
//

#ifndef DOODLEJUMP_JETPACK_H
#define DOODLEJUMP_JETPACK_H

#include "Player.h"

namespace Model {

class Jetpack : public Entity
{
private:
        std::pair<float, float> mBounds;
        bool mMovingDown;
        bool mInit;

public:
        Jetpack() = default;

        ~Jetpack() override = default;

        [[nodiscard]] Model::Type getType() const override;

        void move(bool collision) override;

        void initBounds();

        void visit(Model::Player& player) override { player.setDrag(0.f); }

        bool isRemovable() const override { return mRemoveFlag; }
};
} // namespace Model

#endif // DOODLEJUMP_JETPACK_H
