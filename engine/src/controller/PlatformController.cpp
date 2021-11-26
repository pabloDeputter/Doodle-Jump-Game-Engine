//
// Created by Pablo Deputter on 20/11/2021.
//

#include "controller/PlatformController.h"

using namespace Controller;

void PlatformController::onEvent(const std::string& move, bool isPressed) {}

void PlatformController::onUpdate(bool collision) { mEntity->move(collision); }
