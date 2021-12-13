//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H

#include "ConcreteFactory.h"

#include "World.h"

#include "util/Resourcemanager.h"
#include "util/Stopwatch.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

/**
 * @brief Class for Game
 */
class Game
{
        std::shared_ptr<sf::RenderWindow> mWindow;
        std::unique_ptr<World> mWorld;
        std::shared_ptr<Model::AbstractFactory> mFactory;
public:
        Game() = default;

        explicit Game(unsigned int width = 800, unsigned int height = 1440);

        ~Game() = default;

        void initializeResources();

        void processEvents();

        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

        void render();

        void run();

        void drawHighScoreTable();
};

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
