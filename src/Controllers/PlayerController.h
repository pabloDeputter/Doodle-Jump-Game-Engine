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
        void onEvent(sf::Event event) override;

        void handlePlayerInput(sf::Keyboard::Key key, bool keyIsPressed);
};
} // namespace Controller

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERCONTROLLER_H
