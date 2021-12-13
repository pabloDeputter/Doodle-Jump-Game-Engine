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
        bool mInit;

public:
        VerticalPlatform() : Entity(7, .10f), mBounds({0.f, 0.f}), mMovingDown(true), mInit(false) {}

        ~VerticalPlatform() override = default;

        Model::Type getType() const override;

        void move(bool collision) override;

        void initBounds();
};
} // namespace Model

#endif // DOODLEJUMP_VERTICALPLATFORM_H
