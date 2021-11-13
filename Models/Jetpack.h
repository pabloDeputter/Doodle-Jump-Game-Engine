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
        std::string getType() const override { return "jetpack"; }
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_JETPACK_H
