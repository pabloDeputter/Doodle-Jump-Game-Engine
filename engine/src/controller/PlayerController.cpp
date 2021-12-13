//
// Created by Pablo Deputter on 19/11/2021.
//

#include "controller/PlayerController.h"

using namespace Controller;

void PlayerController::handleEvent(const KeyPressedEvent& event)
{
        auto player = std::dynamic_pointer_cast<Model::Player>(mEntity);
        const std::string& key = event.getKey();
        bool isPressed = event.isPressed();

        if (key == "Q")
                player->setIsMovingLeft(isPressed);
        else if (key == "D")
                player->setIsMovingRight(isPressed);
}

void PlayerController::handleEvent(const MoveEvent& event)
{
        mEntity->move(event.isCollided());

        if (mEntity->getY() < Utils::Camera::getInstance().getY()) {
                mEntity->trigger(EventType::OUT_OF_VIEW, std::make_shared<OutOfViewEvent>());
                return;
        }

        // If player goes out of world dimensions, he will appear on the inverse side
        if (mEntity->getX() < 0.f) {
                mEntity->setX(Utils::Camera::getInstance().getWorldDimensions().first);
        }
        if (mEntity->getX() > 8.f) {
                mEntity->setX(0.f);
        }
}

void PlayerController::handleEvent(const CollisionEvent& event)
{
        auto player = std::dynamic_pointer_cast<Model::Player>(mEntity);
        if (event.getEntity()->isBonus()) {
                // Add Player as Observer to Bonus Subject
                // Allows Bonus Entity to change state of Player
                mEntity->accept(event.getEntity());
                // Move out of world to avoid second collision
                event.getEntity()->setX(Utils::Camera::getInstance().getWorldDimensions().first * 2.f);
                // Bonus can be removed next time world entities are cleared
                event.getEntity()->setRemoveFlag(true);

                event.getEntity()->add(event.getPlayer());
                return;
        }
        if (event.getEntity()->getType() == Model::eTemporary) {
                event.getEntity()->setRemoveFlag(true);
        }
}
