//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERCONTROLLER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERCONTROLLER_H

#include "IController.h"

namespace Controller {

class PlayerController : public IController
{
public:
        PlayerController(std::shared_ptr<Model::Entity>& entity) : IController(entity) {}

        PlayerController() = default;

        ~PlayerController() override = default;

        void onEvent(const std::string& move, bool isPressed) override;

        void handlePlayerInput(const std::string& move, bool keyIsPressed);

        void onUpdate(bool collision) override;
};
} // namespace Controller

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERCONTROLLER_H
