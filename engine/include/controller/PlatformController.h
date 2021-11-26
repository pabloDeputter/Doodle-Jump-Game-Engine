//
// Created by Pablo Deputter on 20/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMCONTROLLER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMCONTROLLER_H

#include "IController.h"
#include "model/Platform.h"

namespace Controller {

class PlatformController : public IController
{
public:
        PlatformController(std::shared_ptr<Model::Entity>& entity) : IController(entity) {}

        PlatformController() = default;

        ~PlatformController() override = default;

        void onEvent(const std::string& move, bool isPressed) override;

        void onUpdate(bool collision) override;
};
} // namespace Controller

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMCONTROLLER_H
