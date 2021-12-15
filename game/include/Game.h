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

#include "State.h"

enum States
{
        eGame = 0,
        eEnterScore,
        eMenu
};

/**
 * @brief Class for Game
 */
class Game
{
public:
        std::shared_ptr<sf::RenderWindow> mWindow;
        std::unique_ptr<World> mWorld;
        std::shared_ptr<Model::AbstractFactory> mFactory;

public:
        std::shared_ptr<State> mState;
        States mStateType;

private:
        static void initializeResources();

public:
        Game() = default;

        explicit Game(unsigned int width = 800, unsigned int height = 1440);

        ~Game() = default;

        void run();
};

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
