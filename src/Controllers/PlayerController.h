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
        PlayerController(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<View::IView>& view)
            : IController(entity, view)
        {
        }

        void onEvent(sf::Event event) override;

        void handlePlayerInput(sf::Keyboard::Key key, bool keyIsPressed);

        void onUpdate() override;
};
} // namespace Controller

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERCONTROLLER_H
