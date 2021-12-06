//
// Created by Pablo Deputter on 21/11/2021.
//

#include "ConcreteFactory.h"

using namespace View;

std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>> ConcreteFactory::createPlayer()
{
        std::shared_ptr<Model::Entity> player = std::make_shared<Model::Player>();
        std::shared_ptr<View::IView> playerView = std::make_shared<View::PlayerView>(player, mWindow);
        std::shared_ptr<Controller::IController> playerController =
            std::make_shared<Controller::PlayerController>(player);
        // Register playerView as Observer to Subject player
        player->add(playerView);

        return {player, playerController};
}

// std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>> ConcreteFactory::createPlatform()
//{
//         std::shared_ptr<Model::Entity> platform = std::make_shared<Model::Platform>();
//         std::shared_ptr<View::IView> platformView = std::make_shared<View::PlatformView>(platform, mWindow);
//         std::shared_ptr<Controller::IController> platformController =
//             std::make_shared<Controller::PlatformController>(platform);
//         // Register platformView as Observer to Subject platform
//         platform->add(platformView);
//         // TODO - initBounds()
//         return {platform, platformController};
// }

std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>>
ConcreteFactory::createStaticPlatform()
{
        std::shared_ptr<Model::Entity> platform = std::make_shared<Model::StaticPlatform>();
        std::shared_ptr<View::IView> platformView = std::make_shared<View::PlatformView>(platform, mWindow);
        std::shared_ptr<Controller::IController> platformController =
            std::make_shared<Controller::PlatformController>(platform);
        platform->add(platformView);

        return {platform, platformController};
}

std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>>
ConcreteFactory::createHorizontalPlatform()
{
        std::shared_ptr<Model::Entity> platform = std::make_shared<Model::HorizontalPlatform>();
        std::shared_ptr<View::IView> platformView = std::make_shared<View::PlatformView>(platform, mWindow);
        std::shared_ptr<Controller::IController> platformController =
            std::make_shared<Controller::PlatformController>(platform);
        platform->add(platformView);

        return {platform, platformController};
}

std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>>
ConcreteFactory::createVerticalPlatform()
{
        std::shared_ptr<Model::Entity> platform = std::make_shared<Model::VerticalPlatform>();
        std::shared_ptr<View::IView> platformView = std::make_shared<View::PlatformView>(platform, mWindow);
        std::shared_ptr<Controller::IController> platformController =
            std::make_shared<Controller::PlatformController>(platform);
        platform->add(platformView);

        return {platform, platformController};
}

std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>>
ConcreteFactory::createTemporaryPlatform()
{
        std::shared_ptr<Model::Entity> platform = std::make_shared<Model::TemporaryPlatform>();
        std::shared_ptr<View::IView> platformView = std::make_shared<View::PlatformView>(platform, mWindow);
        std::shared_ptr<Controller::IController> platformController =
            std::make_shared<Controller::PlatformController>(platform);
        platform->add(platformView);

        return {platform, platformController};
}

std::shared_ptr<Model::Entity> ConcreteFactory::createSpring()
{
        std::shared_ptr<Model::Entity> spring = std::make_shared<Model::Spring>();
        std::shared_ptr<View::IView> springView = std::make_shared<View::BonusView>(spring, mWindow);
        spring->add(springView);

        return spring;
}

std::shared_ptr<Model::Entity> ConcreteFactory::createBackground()
{
        std::shared_ptr<Model::Entity> background = std::make_shared<Model::Background>();
        std::shared_ptr<View::IView> backgroundView = std::make_shared<View::BackgroundView>(background, mWindow);
        background->add(backgroundView);

        background->setX(1.f);
        background->setY(0.f);

        return background;
}
