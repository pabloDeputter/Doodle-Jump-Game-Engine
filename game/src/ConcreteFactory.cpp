//
// Created by Pablo Deputter on 21/11/2021.
//

#include "ConcreteFactory.h"

using namespace Factory;

std::shared_ptr<Model::Player> ConcreteFactory::createPlayer()
{
        std::shared_ptr<Model::Player> player = std::make_shared<Model::Player>();
        std::shared_ptr<View::IView> playerView = std::make_shared<View::PlayerView>(player, mWindow);
        std::shared_ptr<Controller::PlayerController> playerController =
            std::make_shared<Controller::PlayerController>(player);
        player->add(playerView);
        player->add(playerController);

        return player;
}

std::shared_ptr<Model::Entity> ConcreteFactory::createStaticPlatform()
{
        std::shared_ptr<Model::Entity> platform = std::make_shared<Model::StaticPlatform>();
        std::shared_ptr<View::IView> platformView = std::make_shared<View::PlatformView>(platform, mWindow);
        std::shared_ptr<Controller::IController> platformController =
            std::make_shared<Controller::PlatformController>(platform);
        platform->add(platformView);
        platform->add(platformController);

        return platform;
}

std::shared_ptr<Model::Entity> ConcreteFactory::createHorizontalPlatform()
{
        std::shared_ptr<Model::Entity> platform = std::make_shared<Model::HorizontalPlatform>();
        std::shared_ptr<View::IView> platformView = std::make_shared<View::PlatformView>(platform, mWindow);
        std::shared_ptr<Controller::IController> platformController =
            std::make_shared<Controller::PlatformController>(platform);
        platform->add(platformView);
        platform->add(platformController);

        return platform;
}

std::shared_ptr<Model::Entity> ConcreteFactory::createVerticalPlatform()
{
        std::shared_ptr<Model::Entity> platform = std::make_shared<Model::VerticalPlatform>();
        std::shared_ptr<View::IView> platformView = std::make_shared<View::PlatformView>(platform, mWindow);
        std::shared_ptr<Controller::IController> platformController =
            std::make_shared<Controller::PlatformController>(platform);
        platform->add(platformView);
        platform->add(platformController);

        return platform;
}

std::shared_ptr<Model::Entity> ConcreteFactory::createTemporaryPlatform()
{
        std::shared_ptr<Model::Entity> platform = std::make_shared<Model::TemporaryPlatform>();
        std::shared_ptr<View::IView> platformView = std::make_shared<View::PlatformView>(platform, mWindow);
        std::shared_ptr<Controller::IController> platformController =
            std::make_shared<Controller::PlatformController>(platform);
        platform->add(platformView);
        platform->add(platformController);

        return platform;
}

std::shared_ptr<Model::Entity> ConcreteFactory::createSpring()
{
        std::shared_ptr<Model::Entity> spring = std::make_shared<Model::Spring>();
        std::shared_ptr<View::IView> springView = std::make_shared<View::BonusView>(spring, mWindow);
        std::shared_ptr<Controller::IController> springController =
            std::make_shared<Controller::BonusController>(spring);
        spring->add(springView);
        spring->add(springController);

        return spring;
}

std::shared_ptr<Model::Entity> ConcreteFactory::createJetpack()
{
        std::shared_ptr<Model::Entity> jetpack = std::make_shared<Model::Jetpack>(false);
        std::shared_ptr<View::IView> jetpackView = std::make_shared<View::BonusView>(jetpack, mWindow);
        std::shared_ptr<Controller::IController> jetpackController =
            std::make_shared<Controller::BonusController>(jetpack);
        jetpack->add(jetpackView);
        jetpack->add(jetpackController);

        return jetpack;
}

std::shared_ptr<Model::Entity> ConcreteFactory::createBackground()
{
        std::shared_ptr<Model::Entity> background = std::make_shared<Model::Background>();
        std::shared_ptr<View::IView> backgroundView = std::make_shared<View::BackgroundView>(background, mWindow);
        background->add(backgroundView);

        return background;
}

std::shared_ptr<Model::Score> ConcreteFactory::createScore()
{
        std::shared_ptr<Model::Score> score = std::make_shared<Model::Score>();
        std::shared_ptr<View::IView> scoreView = std::make_shared<View::ScoreView>(score, mWindow);
        score->add(scoreView);

        return score;
}
