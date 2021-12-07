//
// Created by Pablo Deputter on 06/12/2021.
//

#ifndef DOODLEJUMP_SPRING_H
#define DOODLEJUMP_SPRING_H

#include "Player.h"
#include <cmath>

namespace Model {

class Spring : public Entity
{
private:
        std::pair<float, float> mBounds;
        bool mMovingDown;
        bool mInit;

public:
        Spring() = default;

        ~Spring() override = default;

        [[nodiscard]] Model::Type getType() const override;

        void move(bool collision) override;

        void initBounds();

        void visit(Model::Player& player) override
        {
                // Original jump with default speed
                float jumpPeak = (player.getMaxVelocity() / player.getDrag()) * (player.getMaxVelocity() / 2.f);
                // Calculate speed needed for a jump with a vertical distance x5
                float newSpeed = sqrt((jumpPeak * 5) * (player.getDrag() * 2.f));
                player.setVelocity({player.getVelocity().first, newSpeed});
        }

        bool isRemovable() const override { return mRemoveFlag; }
};
} // namespace Model

#endif // DOODLEJUMP_SPRING_H
