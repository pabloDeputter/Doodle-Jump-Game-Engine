//
// Created by Pablo Deputter on 13/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORM_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORM_H

#include "Entity.h"

namespace Model {

class Platform : public Entity
{

public:
        enum Sort
        {
                Static = 0,
                Horizontal = 1,
                Vertical = 2,
                Temporary = 3
        };

        Model::Type getType() const override { return Model::Type::ePlatform; }
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORM_H
