//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ICONTROLLER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ICONTROLLER_H

#include "model/Entity.h"
#include "model/Player.h"

#include <memory>

namespace Controller {

class IController
{
protected:
        std::shared_ptr<Model::Entity> mEntity;

public:
        IController(std::shared_ptr<Model::Entity>& entity) : mEntity(entity) {}

        IController() = default;

        virtual ~IController() = default;

        virtual void onEvent(const std::string& move, bool isPressed) = 0;

        virtual void onUpdate(bool collision) = 0;

        const std::shared_ptr<Model::Entity>& getMEntity() const { return mEntity; }
};
} // namespace Controller

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ICONTROLLER_H
