//
// Created by Pablo Deputter on 19/11/2021.
//

#include "controller/IController.h"

using namespace Controller;

void IController::handleEvent(const MoveEvent& event)
{
        mEntity->move(event.isCollided());

        if (mEntity->getY() < Utils::Camera::getInstance().getY()) {
                mEntity->trigger(EventType::OUT_OF_VIEW, std::make_shared<OutOfViewEvent>());
                return;
        }
}
