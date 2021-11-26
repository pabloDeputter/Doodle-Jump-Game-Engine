//
// Created by Pablo Deputter on 19/11/2021.
//

#include "controller/PlayerController.h"

using namespace Controller;

void PlayerController::onEvent(const std::string& move, bool isPressed)
{
        PlayerController::handlePlayerInput(move, isPressed);
}

void PlayerController::handlePlayerInput(const std::string& move, bool isPressed)
{
        auto player = std::dynamic_pointer_cast<Model::Player>(mEntity);

        if (move == "Z")
                player->setIsMovingUp(isPressed);
        else if (move == "S")
                player->setIsMovingDown(isPressed);
        else if (move == "Q")
                player->setIsMovingLeft(isPressed);
        else if (move == "D")
                player->setIsMovingRight(isPressed);
}

void PlayerController::onUpdate(bool collision) { mEntity->move(collision); }
