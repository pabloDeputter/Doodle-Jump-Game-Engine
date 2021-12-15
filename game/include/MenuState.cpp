//
// Created by Pablo Deputter on 14/12/2021.
//

#include "GameState.h"

void MenuState::handleInput(sf::Keyboard::Key key, bool isPressed) const
{
        if (key == sf::Keyboard::C && isPressed) {
                HighScore::getInstance().clear();
        }
}

void MenuState::processEvents()
{
        sf::Event event;
        while (mWindow->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::R) {
                                mGame.mStateType = eGame;
                                return;
                        }
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