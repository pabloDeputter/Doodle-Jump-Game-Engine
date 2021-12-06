//
// Created by Pablo Deputter on 21/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_CONCRETEFACTORY_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_CONCRETEFACTORY_H

#include "AbstractFactory.h"

#include "model/Background.h"
#include "model/HorizontalPlatform.h"
#include "model/Platform.h"
#include "model/Player.h"
#include "model/Spring.h"
#include "model/StaticPlatform.h"
#include "model/TemporaryPlatform.h"
#include "model/VerticalPlatform.h"

#include "controller/PlatformController.h"
#include "controller/PlayerController.h"

#include "view/BackgroundView.h"
#include "view/BonusView.h"
#include "view/IView.h"
#include "view/PlatformView.h"
#include "view/PlayerView.h"

#include "SFML/Graphics.hpp"

// TODO - attach View Observers to Entity Subjects

namespace View {
class ConcreteFactory : public Model::AbstractFactory
{
public:
        ConcreteFactory() = default;

        ConcreteFactory(const std::shared_ptr<sf::RenderWindow>& window) : mWindow(window) {}

        ~ConcreteFactory() override = default;

        std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>> createPlayer() override;

        //        std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>> createPlatform()
        //        override;

        std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>> createStaticPlatform()
            override;

        std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>> createHorizontalPlatform()
            override;

        std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>> createVerticalPlatform()
            override;

        std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>> createTemporaryPlatform()
            override;

        std::shared_ptr<Model::Entity> createSpring() override;

        std::shared_ptr<Model::Entity> createBackground() override;

private:
        std::shared_ptr<sf::RenderWindow> mWindow;
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_CONCRETEFACTORY_H
