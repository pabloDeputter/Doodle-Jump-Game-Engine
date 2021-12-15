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

#include "Score.h"

#include "SFML/Graphics.hpp"

// TODO - attach View Observers to Entity Subjects

namespace View {
class ConcreteFactory : public Model::AbstractFactory
{
public:
        ConcreteFactory() = default;

        ConcreteFactory(const std::shared_ptr<sf::RenderWindow>& window) : mWindow(window) {}

        ~ConcreteFactory() override = default;

        std::shared_ptr<Model::Player> createPlayer() override;

        std::shared_ptr<Model::Entity> createStaticPlatform() override;

        std::shared_ptr<Model::Entity> createHorizontalPlatform() override;

        std::shared_ptr<Model::Entity> createVerticalPlatform() override;

        std::shared_ptr<Model::Entity> createTemporaryPlatform() override;

        std::shared_ptr<Model::Entity> createSpring() override;

        std::shared_ptr<Model::Entity> createJetpack() override;

        std::shared_ptr<Model::Entity> createBackground() override;

        std::shared_ptr<Model::Score> createScore() override;

private:
        std::shared_ptr<sf::RenderWindow> mWindow;
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_CONCRETEFACTORY_H
