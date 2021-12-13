//
// Created by Pablo Deputter on 21/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ABSTRACTFACTORY_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ABSTRACTFACTORY_H

#include "Score.h"
#include "controller/IController.h"
#include "model/Entity.h"

namespace Model {
// Used by world to create new entities without knowing anything sfml-related (VIEW)

// The game class provides pointer to concrete factory to world, so it can create
// entities that have correct view attached
class AbstractFactory
{
public:
        AbstractFactory() = default;

        virtual ~AbstractFactory() = default;

        virtual std::shared_ptr<Model::Player> createPlayer() = 0;

        virtual std::shared_ptr<Model::Entity> createStaticPlatform() = 0;

        virtual std::shared_ptr<Model::Entity> createHorizontalPlatform() = 0;

        virtual std::shared_ptr<Model::Entity> createVerticalPlatform() = 0;

        virtual std::shared_ptr<Model::Entity> createTemporaryPlatform() = 0;

        virtual std::shared_ptr<Model::Entity> createSpring() = 0;

        virtual std::shared_ptr<Model::Entity> createJetpack() = 0;

        virtual std::shared_ptr<Model::Entity> createBackground() = 0;

        virtual std::shared_ptr<Model::Score> createScore(float x, float y) = 0;
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ABSTRACTFACTORY_H
