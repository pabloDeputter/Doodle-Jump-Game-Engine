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
        std::shared_ptr<View::IView> mView;

public:
        IController(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<View::IView>& view)
            : mEntity(entity), mView(view)
        {
        }

        IController() = default;

        virtual ~IController() = default;

        virtual void onEvent(sf::Event event) = 0;

        virtual void onUpdate() = 0;
};
} // namespace Controller

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ICONTROLLER_H
