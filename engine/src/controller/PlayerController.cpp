//
// Created by Pablo Deputter on 19/11/2021.
//

#include "controller/PlayerController.h"

#include "util/Camera.h"

using namespace Controller;

void PlayerController::handleEvent(const KeyPressedEvent& event)
{
        const std::string& key = event.getKey();
        bool isPressed = event.isPressed();
        // Set correct moving state of Player
        if (key == "Q")
                mEntity->setIsMovingLeft(isPressed);
        else if (key == "D")
                mEntity->setIsMovingRight(isPressed);
        else if (key == "SPACE")
                mEntity->setIsMovingUp(isPressed);
}

void PlayerController::handleEvent(const MoveEvent& event)
{
        // Move Player
        mEntity->move(event.isCollided());
        // If Player is out of view, trigger OutOfViewEvent
        if (mEntity->getY() < Utils::Camera::getInstance().getY()) {
                mEntity->trigger(EventType::OUT_OF_VIEW, std::make_shared<OutOfViewEvent>());
                return;
        }

        // If player goes out of world dimensions, he will appear on the inverse side
        if (mEntity->getX() < 0.f) {
                mEntity->setX(Utils::Camera::getInstance().getWorldDimensions().first);
        }
        if (mEntity->getX() > Utils::Camera::getInstance().getWorldDimensions().first) {
                mEntity->setX(0.f);
        }
}

void PlayerController::handleEvent(const CollisionEvent& event)
{
        // TODO - idk
        if (event.getEntity()->isBonus()) {
                // Allows Bonus Entity to change state of Player
                mEntity->accept(event.getEntity());
                // Move out of world to avoid second collision
                event.getEntity()->setX(Utils::Camera::getInstance().getWorldDimensions().first * 2.f);
                // Bonus can be removed next time world entities are cleared
                event.getEntity()->setRemoveFlag(true);

                event.getEntity()->add(event.getPlayer());
                return;
        }
}
