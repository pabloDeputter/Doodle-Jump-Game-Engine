//
// Created by Pablo Deputter on 18/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_WORLD_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_WORLD_H

#include "Entity/Entity.h"
#include "Entity/Player.h"

#include <memory>
#include <vector>

class World
{
private:
        int mScore;
        std::unique_ptr<Model::Player> mPlayer;
        std::vector<std::shared_ptr<Model::Entity>> mEntities;

public:
        World() = default;

        ~World() = default;
};

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_WORLD_H
