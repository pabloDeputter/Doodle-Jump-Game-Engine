//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H

#include "World.h"
#include "util/Stopwatch.h"

#include "ConcreteFactory.h"
#include "state/State.h"
#include "util/ResourceManager.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

/**
 * @brief Game states
 */
enum GameStates
{
        ePlay = 0,
        eEnterScore,
        eMenu
};

/**
 * @brief Class for Game
 */
class Game
{
public:
        std::shared_ptr<sf::RenderWindow> mWindow;          /**< Pointer to window */
        std::shared_ptr<Factory::AbstractFactory> mFactory; /**< Pointer to Factory */
        std::shared_ptr<State> mState;                      /**< Pointer to current State */
        GameStates mStateType;                              /**< Type of current State */

private:
        /**
         * @brief Initialize resources
         */
        static void initializeResources();
        /**
         * @brief Check if Game is still in correct State
         */
        void checkState();

public:
        /**
         * @brief Constructor for Game object
         * @param width unsigned int - width of screen, standard = 800
         * @param height unsigned int - height of screen, standard = 1440
         */
        explicit Game(unsigned int width = 800, unsigned int height = 1440);
        /**
         * @brief Destructor for Game object
         */
        ~Game() = default;
        /**
         * @brief Run main Game loop
         */
        void run();
};

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
