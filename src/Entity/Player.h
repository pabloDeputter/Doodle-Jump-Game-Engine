//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYER_H

#include "Entity.h"

namespace Model {

class Player : public Entity
{
public:
        Model::Type getType() const override { return Model::Type::ePlayer; }
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYER_H
