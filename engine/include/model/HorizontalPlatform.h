//
// Created by Pablo Deputter on 05/12/2021.
//

#ifndef DOODLEJUMP_HORIZONTALPLATFORM_H
#define DOODLEJUMP_HORIZONTALPLATFORM_H

#include "Entity.h"
#include "util/Random.h"

namespace Model {

class HorizontalPlatform : public Entity
{
private:
        std::pair<float, float> mBounds;
        bool mMovingForward;
        float mSpeed;
        bool mInit;

public:
        HorizontalPlatform() : Entity(5), mBounds({0.f, 0.f}), mInit(false)
        {
                if (Utils::Random::getInstance().random(0.f, 1.f) >= 0.5f) {
                        mMovingForward = false;
                } else {
                        mMovingForward = true;
                }

                mSpeed = Utils::Random::getInstance().random(.02f, .05f);
        }

        ~HorizontalPlatform() override = default;

        [[nodiscard]] Model::Type getType() const override { return Model::eHorizontal; }

        void move(bool collision) override;

        void initBounds();
};
} // namespace Model

#endif // DOODLEJUMP_HORIZONTALPLATFORM_H
