//
// Created by Pablo Deputter on 14/12/2021.
//

#ifndef DOODLEJUMP_STATE_H
#define DOODLEJUMP_STATE_H

#include "SFML/Graphics.hpp"

#include <utility>

// Forward declaration
class Game;

/**
 * @brief Abstract class for Game State
 */
class State
{
protected:
        Game& mGame;                               /**< Game */
        std::shared_ptr<sf::RenderWindow> mWindow; /**< Pointer to renderWindow */
public:
        /**
         * @brief Constructor for State object
         * @param window sf::RenderWindow - window to draw on
         * @param game Game - current game
         */
        State(std::shared_ptr<sf::RenderWindow> window, Game& game) : mGame(game), mWindow(std::move(window)) {}
        /**
         * @brief Destructor for State object
         */
        virtual ~State() = default;
        /**
         * @brief Render State - PURE VIRTUAL
         */
        virtual void render() const = 0;
        /**
         * @brief Update State - PURE VIRTUAL
         */
        virtual void update() = 0;
        /**
         * @brief Process events - PURE VIRTUAL
         */
        virtual void processEvents() = 0;
        /**
         * @brief Get type of State - PURE VIRTUAL
         * @return GameState - type of State
         */
        [[nodiscard]] virtual unsigned int getType() const = 0;
};

#endif // DOODLEJUMP_STATE_H
