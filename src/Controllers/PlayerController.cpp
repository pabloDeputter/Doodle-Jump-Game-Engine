//
// Created by Pablo Deputter on 19/11/2021.
//

#include "PlayerController.h"

using namespace Controller;

void PlayerController::onEvent(sf::Event event)
{
        switch (event.type) {
        case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
        case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
        }
}

void PlayerController::handlePlayerInput(sf::Keyboard::Key key, bool keyIsPressed)
{
        auto player = std::dynamic_pointer_cast<Model::Player>(mEntity);

        if (key == sf::Keyboard::Z) {
                player->mIsMovingUp = keyIsPressed;
        } else if (key == sf::Keyboard::S) {
                player->mIsMovingDown = keyIsPressed;
        } else if (key == sf::Keyboard::Q) {
                player->mIsMovingLeft = keyIsPressed;
        } else if (key == sf::Keyboard::D) {
                player->mIsMovingRight = keyIsPressed;
        }
}
