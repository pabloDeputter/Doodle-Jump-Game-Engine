//
// Created by Pablo Deputter on 18/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_WORLD_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_WORLD_H

#include "model/Entity.h"
#include "model/Player.h"

#include "AbstractFactory.h"

#include "util/Camera.h"
#include "util/Random.h"
#include "util/Utilities.h"

#include "Settings.h"
#include "model/Score.h"
#include "observer/Events.h"

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
        std::shared_ptr<Factory::AbstractFactory>
            mFactory; /**< Pointer to AbstractFactory, is used to create Entities */
        std::vector<std::shared_ptr<Model::Entity>> mBackground; /**< std::vector containing Background-tiles */
        std::shared_ptr<Model::Score> mScore;                    /**< Pointer to Score */
        unsigned int mActivePlatforms;                           /**< Holds the active amount of platforms */
        Settings::Difficulty mDifficulty;                        /**< Current Difficulty of game */
        bool mPlaying;                                           /**< True if Player is not dead */

private:
        /**
         * @brief Generate new Entity
         */
        void generateEntity();
        /**
         * @brief Spawn random Platform object into World
         * @param x float - X coordinate of Platform
         * @param y float - Y coordinate of Platform
         */
        void spawnPlatform(float x, float y);
        /**
         * @brief Spawn random Bonus object AND Platform object into World
         * @param x float - X coordinate of Bonus
         * @param y float - Y coordinate of Bonus
         */
        void spawnBonus(float x, float y);
        /**
         * @brief Spawn provided Entity into World
         * @param x float
         * @param y float
         * @param type Model::Type - Sort of Entity to be spawned
         */
        void spawnEntity(float x, float y, Model::Type type);
        /**
         * @brief Check if Difficulty of game can be changed
         * @return bool - true if Difficulty has changed
         */
        bool checkDifficulty();
        /**
         * @brief Add entity
         * @param entity Entity to be added to mEntities
         */
        void addEntity(const std::shared_ptr<Model::Entity>& entity) { mEntities.emplace_back(entity); }
        /**
         * @brief Remove unused Entities or those that are out of view
         */
        void removeEntities();

public:
        /**
         * @brief Constructor for World object
         * @param factory Pointer to Model::AbstractFactory
         * @param playing bool - Player is not dead
         * @param diff Settings::Difficulty - difficulty of game
         */
        explicit World(std::shared_ptr<Factory::AbstractFactory>& factory, bool playing,
                       Settings::Difficulty diff = Settings::eEasy);
        /**
         * @brief Destructor for World object
         */
        ~World() { destroy(); }
        /**
         * @brief Initialize starting-world, such as starting platforms, background, ...
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
         * @brief Destroy World
         */
        void destroy();
        /**
         * @brief Get current score of game
         * @return Model::Score - Pointer to Model::Score object
         */
        [[nodiscard]] const std::shared_ptr<Model::Score>& getScore() const { return mScore; }
        /**
         * @brief Check if Player is not dead
         * @return bool - true if Player is not dead
         */
        [[nodiscard]] bool isPlaying() const { return mPlaying; }
};

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_WORLD_H
