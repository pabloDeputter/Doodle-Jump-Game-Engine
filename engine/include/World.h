//
// Created by Pablo Deputter on 18/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_WORLD_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_WORLD_H

#include "controller/IController.h"
#include "controller/PlayerController.h"

#include "model/Entity.h"
#include "model/Player.h"

#include "AbstractFactory.h"

#include "model/Jetpack.h"

#include "Score.h"
#include "util/Camera.h"
#include "util/Random.h"
#include "util/Utilities.h"

#include "Settings.h"

#include "Event.h"

#include <iostream>
#include <memory>
#include <vector>

/**
 * @brief Class for World, holds all the entities and is used for the overall game logic
 */
class World
{
private:
        std::shared_ptr<Model::Player> mPlayer;                /**< Pointer to Player */
        std::vector<std::shared_ptr<Model::Entity>> mEntities; /**< std::vector containing Entities */
        std::shared_ptr<Model::AbstractFactory> mFactory; /**< Pointer to AbstractFactory, is used to create Entities */
        std::vector<std::shared_ptr<Model::Entity>> mBackground; /**< std::vector containing Background-tiles */
        std::shared_ptr<Model::Score> mScore;                    /**< Pointer to Score */
        unsigned int mActivePlatforms;                           /**< Holds the active amount of platforms */
        Settings::Difficulty mDifficulty;

public:
        explicit World(std::shared_ptr<Model::AbstractFactory>& factory);

        ~World() = default;
        /**
         * @brief Initialize starting-world
         */
        void initWorld();
        /**
         * @brief Process events such as player input
         * @param move std::string - which key is pressed
         * @param isPressed bool - is key pressed
         */
        void events(const std::string& move, bool isPressed) const;
        /**
         * @brief Gets called every tick from Game loop, updates ever Model
         */
        void update();
        /**
         * @brief Render all entities on screen
         */
        void render() const;
        /**
         * @brief Generate new Entity
         */
        void generateEntity();
        /**
         * @brief Spawn random Platform object into World
         * @param x float
         * @param y float
         */
        void spawnPlatform(float x, float y);
        /**
         * @brief Spawn random Bonus object AND Platform object into World
         * @param x float
         * @param y float
         */
        void spawnBonus(float x, float y);
        /**
         * @brief Spawn provided Entity into World
         * @param x float
         * @param y float
         * @param type Model::Type - Sort of Entity to be spawned
         */
        void spawnEntity(float x, float y, Model::Type type);
        bool checkDifficulty();
        /**
         * @brief Add entity
         * @param entity Entity to be added to mEntities
         */
        void addEntity(const std::shared_ptr<Model::Entity>& entity);
        /**
         * @brief Remove unused Entities or those that are out of view
         */
        void removeEntities();
};

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_WORLD_H
