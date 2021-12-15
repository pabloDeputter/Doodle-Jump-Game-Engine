//
// Created by Pablo Deputter on 21/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_CONCRETEFACTORY_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_CONCRETEFACTORY_H

#include "AbstractFactory.h"

#include "model/Background.h"
#include "model/HorizontalPlatform.h"
#include "model/Jetpack.h"
#include "model/Player.h"
#include "model/Score.h"
#include "model/Spring.h"
#include "model/StaticPlatform.h"
#include "model/TemporaryPlatform.h"
#include "model/VerticalPlatform.h"

#include "controller/BonusController.h"
#include "controller/PlatformController.h"
#include "controller/PlayerController.h"

#include "view/BackgroundView.h"
#include "view/BonusView.h"
#include "view/IView.h"
#include "view/PlatformView.h"
#include "view/PlayerView.h"
#include "view/ScoreView.h"

#include "SFML/Graphics.hpp"

/**
 * @brief Namespace holds Factory design pattern
 */
namespace Factory {
/**
 * @brief Class for Concrete Factory, implements AbstractFactory's methods
 */
class ConcreteFactory : public Factory::AbstractFactory
{
private:
        std::shared_ptr<sf::RenderWindow> mWindow; /**< Pointer to renderWindow */
public:
        /**
         * @brief Default constructor for ConcreteFactory object
         */
        ConcreteFactory() = default;
        /**
         * @brief Constructor for ConcreteFactory object
         * @param window sf::RenderWindow - pointer to window
         */
        explicit ConcreteFactory(const std::shared_ptr<sf::RenderWindow>& window) : mWindow(window) {}
        /**
         * @brief Default destructor for ConcreteFactory object
         */
        ~ConcreteFactory() override = default;
        /**
         * @brief Create Player object
         * @return Model::Player - pointer to Player
         */
        std::shared_ptr<Model::Player> createPlayer() override;
        /**
         * @brief Create StaticPlatform object
         * @return Model::Entity - pointer to Entity
         */
        std::shared_ptr<Model::Entity> createStaticPlatform() override;
        /**
         * @brief Create HorizontalPlatform object
         * @return Model::Entity - pointer to Entity
         */
        std::shared_ptr<Model::Entity> createHorizontalPlatform() override;
        /**
         * @brief Create VerticalPlatform object
         * @return Model::Entity - pointer to Entity
         */
        std::shared_ptr<Model::Entity> createVerticalPlatform() override;
        /**
         * @brief Create TemporaryPlatform object
         * @return Model::Entity - pointer to Entity
         */
        std::shared_ptr<Model::Entity> createTemporaryPlatform() override;
        /**
         * @brief Create Spring object
         * @return Model::Entity - pointer to Entity
         */
        std::shared_ptr<Model::Entity> createSpring() override;
        /**
         * @brief Create Jetpack object
         * @return Model::Entity - pointer to Entity
         */
        std::shared_ptr<Model::Entity> createJetpack() override;
        /**
         * @brief Create Background object
         * @return Model::Entity - pointer to Entity
         */
        std::shared_ptr<Model::Entity> createBackground() override;
        /**
         * @brief Create Score object
         * @return Model::Entity - pointer to Entity
         */
        std::shared_ptr<Model::Score> createScore() override;
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_CONCRETEFACTORY_H
