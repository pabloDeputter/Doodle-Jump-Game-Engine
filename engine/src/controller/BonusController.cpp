//
// Created by Pablo Deputter on 07/12/2021.
//

#include "controller/BonusController.h"

using namespace Controller;

void BonusController::onEvent(const std::string& move, bool isPressed) {}

void BonusController::onUpdate(bool collision) { mEntity->move(collision); }