//
// Created by Pablo Deputter on 14/12/2021.
//

#ifndef DOODLEJUMP_GAMESTATE_H
#define DOODLEJUMP_GAMESTATE_H

#include "MenuState.h"
#include "State.h"

#include "Game.h"

#include "World.h"
#include <utility>

class GameState : public State
{
private:
        std::unique_ptr<World> mWorld;

private:
        void render() override
        {
                mWindow->clear(sf::Color::White);
                mWorld->render();
                mWindow->display();
        }

        void update() override
        {
                mWorld->update();
                if (!mWorld->isPlaying()) {
                        const int score = mWorld->getScore()->getScore();
                        if (HighScore::getInstance().isHighScore(score)) {
                                HighScore::getInstance().add(score);
                                mGame.mStateType = eEnterScore;
                        } else {
                                mGame.mStateType = eMenu;
                        }
                }
        }

        void handleInput(sf::Keyboard::Key key, bool isPressed) const
        {
                if (key == sf::Keyboard::Z) {
                        mWorld->events("Z", isPressed);
                } else if (key == sf::Keyboard::S) {
                        mWorld->events("S", isPressed);
                } else if (key == sf::Keyboard::Q) {
                        mWorld->events("Q", isPressed);
                } else if (key == sf::Keyboard::D) {
                        mWorld->events("D", isPressed);
                }
        }

        void processEvents() override
        {
                sf::Event event;
                while (mWindow->pollEvent(event)) {
                        switch (event.type) {
                        case sf::Event::KeyPressed:
                                handleInput(event.key.code, true);
                                break;
                        case sf::Event::KeyReleased:
                                handleInput(event.key.code, false);
                                break;
                        case sf::Event::Closed:
                                mWindow->close();
                                break;
                        }
                }
        }

public:
        GameState(std::unique_ptr<World> world, std::shared_ptr<sf::RenderWindow> window, Game& game)
            : State(std::move(window), game), mWorld(std::move(world))
        {
                Utils::Camera::getInstance().reset();
                Utils::Stopwatch::getInstance().reset();
                mWorld->initWorld();
        }

        ~GameState() override { mWorld->destroy(); }

        [[nodiscard]] unsigned int getType() override { return eGame; }
};

#endif // DOODLEJUMP_GAMESTATE_H
