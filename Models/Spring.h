//
// Created by Pablo Deputter on 13/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_SPRING_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_SPRING_H

#include "Entity.h"

namespace Model {

class Spring : public Entity
{
public:
        std::string getType() const override { return "spring"; }
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_SPRING_H
