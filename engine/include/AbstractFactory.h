//
// Created by Pablo Deputter on 21/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ABSTRACTFACTORY_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ABSTRACTFACTORY_H

#include "controller/IController.h"
#include "model/Entity.h"

namespace Model {
// Used by world to create new entities without knowing knowing anything sfml-related (VIEW)

// The game class provides pointer to concrete factory to world, so it can create
// entities that have correct view attached
class AbstractFactory
{
public:
        AbstractFactory() = default;

        virtual ~AbstractFactory() = default;

        virtual std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>> createPlayer() = 0;

        //        virtual std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>>
        //        createPlatform() = 0;

        virtual std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>>
        createStaticPlatform() = 0;

        virtual std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>>
        createHorizontalPlatform() = 0;

        virtual std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>>
        createVerticalPlatform() = 0;

        virtual std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>>
        createTemporaryPlatform() = 0;

        virtual std::shared_ptr<Model::Entity> createSpring() = 0;

        virtual std::shared_ptr<Model::Entity> createBackground() = 0;
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ABSTRACTFACTORY_H
