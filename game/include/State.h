//
// Created by Pablo Deputter on 14/12/2021.
//

#ifndef DOODLEJUMP_STATE_H
#define DOODLEJUMP_STATE_H

#include "SFML/Graphics.hpp"
#include <utility>

class Game;

class State
{
protected:
        Game& mGame;
        std::shared_ptr<sf::RenderWindow> mWindow;
public:
        State(std::shared_ptr<sf::RenderWindow> window, Game& game)
            : mGame(game), mWindow(std::move(window)) {}

        virtual ~State() = default;

        virtual void update() = 0;

        virtual void render() = 0;

        virtual void processEvents() = 0;

        virtual unsigned int getType() = 0;
};

#endif // DOODLEJUMP_STATE_H
