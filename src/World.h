//
// Created by Pablo Deputter on 18/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_WORLD_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_WORLD_H

#include "Entity/Entity.h"

#include <memory>
#include <vector>

class World
{
private:
        std::vector<std::shared_ptr<Model::Entity>> mEntities;
};

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_WORLD_H
