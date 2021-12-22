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

#include <stack>

/**
 * @brief Game states
 */
enum GameStates
{
        ePlay = 0,
        eMenu,
        eSettings,
        eShop
};

/**
 * @brief Class for Game
 */
class Game
{
private:
        std::shared_ptr<sf::RenderWindow> mWindow;          /**< Pointer to window */
        std::shared_ptr<Factory::AbstractFactory> mFactory; /**< Pointer to Factory */
        std::stack<std::shared_ptr<State>> mStates;         /**< Stack of states */

private:
        /**
         * @brief Initialize resources
         */
        static void initializeResources();

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
        ~Game()
        {
                while (!mStates.empty()) {
                        mStates.pop();
                }
        }
        /**
         * @brief Run main Game loop
         */
        void run();
        /**
         * @brief Get factory
         * @return Factory::AbstractFactory - factory
         */
        std::shared_ptr<Factory::AbstractFactory>& getFactory() { return mFactory; }
        /**
         * @brief Push state onto GameStates stack
         * @param state State - state to be pushed
         */
        void pushState(const std::shared_ptr<State>& state) { mStates.push(state); }
        /**
         * @brief Pop State from GameStates stack
         */
        void popState() { mStates.pop(); }
        /**
         * @brief Get top of GameStates stack
         * @return State - top of stack
         */
        std::shared_ptr<State>& peekState() { return mStates.top(); }
};

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
