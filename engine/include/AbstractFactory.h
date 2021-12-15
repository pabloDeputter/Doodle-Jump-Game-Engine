//
// Created by Pablo Deputter on 21/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ABSTRACTFACTORY_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ABSTRACTFACTORY_H

#include "model/Entity.h"
#include "model/Score.h"

/**
 * @brief Namespace holds Factory design pattern
 */
namespace Factory {
/**
 * @brief Class for Abstract Factory, used by World to create new entities without knowing anything SFML-related. The
 * Game class shall provide a ConcreteFactory pointer to world, such it can create entities that have already
 * the correct view attached.
 */
class AbstractFactory
{
public:
        /**
         * @brief Default constructor for AbstractFactory object
         */
        AbstractFactory() = default;
        /**
         * @brief Default destructor for AbstractFactory object
         */
        virtual ~AbstractFactory() = default;
        /**
         * @brief Create Player object
         * @return Model::Player - pointer to Player
         */
        virtual std::shared_ptr<Model::Player> createPlayer() = 0;
        /**
         * @brief Create StaticPlatform object - PURE VIRTUAL
         * @return Model::Entity - pointer to Entity
         */
        virtual std::shared_ptr<Model::Entity> createStaticPlatform() = 0;
        /**
         * @brief Create HorizontalPlatform object - PURE VIRTUAL
         * @return Model::Entity - pointer to Entity
         */
        virtual std::shared_ptr<Model::Entity> createHorizontalPlatform() = 0;
        /**
         * @brief Create VerticalPlatform object - PURE VIRTUAL
         * @return Model::Entity - pointer to Entity
         */
        virtual std::shared_ptr<Model::Entity> createVerticalPlatform() = 0;
        /**
         * @brief Create TemporaryPlatform object - PURE VIRTUAL
         * @return Model::Entity - pointer to Entity
         */
        virtual std::shared_ptr<Model::Entity> createTemporaryPlatform() = 0;
        /**
         * @brief Create Spring object - PURE VIRTUAL
         * @return Model::Entity - pointer to Entity
         */
        virtual std::shared_ptr<Model::Entity> createSpring() = 0;
        /**
         * @brief Create Jetpack object - PURE VIRTUAL
         * @return Model::Entity - pointer to Entity
         */
        virtual std::shared_ptr<Model::Entity> createJetpack() = 0;
        /**
         * @brief Create Background object - PURE VIRTUAL
         * @return Model::Entity - pointer to Entity
         */
        virtual std::shared_ptr<Model::Entity> createBackground() = 0;
        /**
         * @brief Create Score object - PURE VIRTUAL
         * @return Model::Entity - pointer to Entity
         */
        virtual std::shared_ptr<Model::Score> createScore() = 0;
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ABSTRACTFACTORY_H
