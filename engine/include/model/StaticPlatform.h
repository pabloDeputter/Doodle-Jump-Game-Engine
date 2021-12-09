//
// Created by Pablo Deputter on 05/12/2021.
//

#ifndef DOODLEJUMP_STATICPLATFORM_H
#define DOODLEJUMP_STATICPLATFORM_H

#include "Entity.h"

namespace Model {

class StaticPlatform : public Entity
{

public:
        StaticPlatform() = default;

        ~StaticPlatform() override = default;

        Model::Type getType() const override;

        void move(bool collision) override;
};
} // namespace Model

#endif // DOODLEJUMP_STATICPLATFORM_H
