//
// Created by Pablo Deputter on 07/12/2021.
//

#ifndef DOODLEJUMP_BONUSCONTROLLER_H
#define DOODLEJUMP_BONUSCONTROLLER_H

#include "IController.h"

namespace Controller {

class BonusController : public IController
{
public:
        BonusController(std::shared_ptr<Model::Entity>& entity) : IController(entity) {}

        BonusController() = default;

        ~BonusController() override = default;
};
} // namespace Controller

#endif // DOODLEJUMP_BONUSCONTROLLER_H
