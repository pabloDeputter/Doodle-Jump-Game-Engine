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
        bool mInit;

public:
        HorizontalPlatform() : mBounds({0.f, 0.f}), mMovingForward(false), mInit(false) {}

        ~HorizontalPlatform() override = default;

        Model::Type getType() const override;

        void move(bool collision) override;

        void initBounds();
};
} // namespace Model

#endif // DOODLEJUMP_HORIZONTALPLATFORM_H
