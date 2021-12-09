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
        explicit PlayerController(std::shared_ptr<Model::Entity>& entity) : IController(entity) {}

        explicit PlayerController(std::shared_ptr<Model::Player>& entity) { mEntity = entity; }

        PlayerController() = default;

        ~PlayerController() override = default;

        void handleEvent(const KeyPressedEvent& event) override;

        void handleEvent(const MoveEvent& event) override;

        void handleEvent(const CollisionEvent& event) override;
};
} // namespace Controller

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERCONTROLLER_H
