//
// Created by Pablo Deputter on 05/12/2021.
//

#ifndef DOODLEJUMP_VERTICALPLATFORM_H
#define DOODLEJUMP_VERTICALPLATFORM_H

#include "Entity.h"
#include "util/Random.h"

namespace Model {

class VerticalPlatform : public Entity
{
private:
        std::pair<float, float> mBounds;
        bool mMovingDown;
        float mSpeed;
        bool mInit;

public:
        VerticalPlatform() : Entity(7), mBounds({0.f, 0.f}), mInit(false)
        {
                if (Utils::Random::getInstance().random(0.f, 1.f) >= 0.5f) {
                        mMovingDown = false;
                } else {
                        mMovingDown = true;
                }

                mSpeed = Utils::Random::getInstance().random(.01f, .025f);
        }

        ~VerticalPlatform() override = default;

        [[nodiscard]] Model::Type getType() const override { return Model::eVertical; }

        void move(bool collision) override;

        void initBounds();
};
} // namespace Model

#endif // DOODLEJUMP_VERTICALPLATFORM_H
