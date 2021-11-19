//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ICONTROLLER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ICONTROLLER_H

#include "../Models/Entity/Entity.h"
#include "../Models/Entity/Player.h"
#include "../Views/IView.h"

#include <memory>

namespace Controller {

class IController
{
protected:
        std::shared_ptr<Model::Entity> mEntity;
        std::unique_ptr<View::IView> mView;

public:
        IController() = default;

        virtual ~IController() = default;

        virtual void onEvent(sf::Event event) = 0;
};
} // namespace Controller

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ICONTROLLER_H
