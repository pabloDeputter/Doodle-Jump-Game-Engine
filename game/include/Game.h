//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H

#include "ConcreteFactory.h"

#include "controller/PlayerController.h"
#include "view/PlayerView.h"

#include "World.h"

#include "util/Resourcemanager.h"
#include "util/Stopwatch.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>

/**
 * @brief Class for Game
 */
class Game
{
        std::shared_ptr<sf::RenderWindow> mWindow;
        std::unique_ptr<World> mWorld;
        std::shared_ptr<Model::AbstractFactory> mFactory;

public:
        Game();

        ~Game() = default;

        void processEvents();

        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

        void render();

        void run();
};

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
