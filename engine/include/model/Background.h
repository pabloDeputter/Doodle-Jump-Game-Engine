//
// Created by Pablo Deputter on 29/11/2021.
//

#ifndef DOODLEJUMP_BACKGROUND_H
#define DOODLEJUMP_BACKGROUND_H

#include "Entity.h"

namespace Model {

class Background : public Entity
{
private:
public:
        Background() = default;

        ~Background() override = default;

        Model::Type getType() const override { return Model::Type::eBackground; }

        void move(bool collision) override {}
};
} // namespace Model

#endif // DOODLEJUMP_BACKGROUND_H
