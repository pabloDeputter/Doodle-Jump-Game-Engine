//
// Created by Pablo Deputter on 18/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_WORLD_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_WORLD_H

#include "controller/IController.h"
#include "model/Entity.h"
#include "model/Player.h"

#include "AbstractFactory.h"

#include "util/Camera.h"
#include "util/Collision.h"

#include <iostream>
#include <memory>
#include <vector>

class World
{
private:
        std::shared_ptr<Controller::IController> mPlayerController;
        std::shared_ptr<Model::Entity> mPlayer;

        std::vector<std::shared_ptr<Model::Entity>> mEntities;
        std::vector<std::shared_ptr<Controller::IController>> mControllers;

        std::shared_ptr<Model::AbstractFactory> mFactory;

        std::vector<std::shared_ptr<Model::Entity>> mBackground;

public:
        World(std::shared_ptr<Model::AbstractFactory>& factory);

        ~World() = default;
        /**
         * @brief Process events such as player input
         * @param move std::string - which key is pressed
         * @param isPressed bool - is key pressed
         */
        void events(const std::string& move, bool isPressed);
        /**
         * @brief Gets called every tick in game loop
         */
        void update();
        /**
         * @brief Render all entities on screen
         */
        void render();

        void addEntity(
            const std::pair<std::shared_ptr<Model::Entity>, const std::shared_ptr<Controller::IController>>& entity);

        void addBackground(const std::shared_ptr<Model::Entity>& entity);

        void addPlayer(
            const std::pair<std::shared_ptr<Model::Entity>, const std::shared_ptr<Controller::IController>>& entity);

        void createBackground();
};

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_WORLD_H
