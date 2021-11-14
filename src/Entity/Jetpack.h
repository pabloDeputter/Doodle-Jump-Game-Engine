//
// Created by Pablo Deputter on 13/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_JETPACK_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_JETPACK_H

#include "Entity.h"

namespace Model {

class Jetpack : public Entity
{
public:
        Model::Type getType() const override { return Model::Type::eJetpack; }
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_JETPACK_H
