//
// Created by Pablo Deputter on 16/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_BONUS_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_BONUS_H

#include "Entity.h"

namespace Model {

class Bonus : public Entity
{

public:
        enum Sort
        {
                eJetpack = 0,
                eSpring = 1,
        };

        Model::Type getType() const override { return Model::Type::eBonus; }
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_BONUS_H
