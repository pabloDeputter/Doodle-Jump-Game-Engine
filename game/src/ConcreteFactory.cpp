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
        player->registerObserver(playerView);

        player->setX(Utils::Camera::getInstance().getGameDimensions().first / 2.f);
        player->setY(Utils::Camera::getInstance().getGameDimensions().second / 2.f);

        //        // TODO - remove
        //        player->setX(.f);
        //        player->setY(0.f);

        return {player, playerController};
}

std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>>
ConcreteFactory::createStaticPlatform()
{
        std::shared_ptr<Model::Entity> platform = std::make_shared<Model::Platform>(Model::eStatic);
        std::shared_ptr<View::IView> platformView = std::make_shared<View::PlatformView>(platform, mWindow);
        std::shared_ptr<Controller::IController> platformController =
            std::make_shared<Controller::PlatformController>(platform);
        platform->registerObserver(platformView);

        return {platform, platformController};
}

std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Controller::IController>> ConcreteFactory::createPlatform()
{
        std::shared_ptr<Model::Entity> platform = std::make_shared<Model::Platform>();
        std::shared_ptr<View::IView> platformView = std::make_shared<View::PlatformView>(platform, mWindow);
        std::shared_ptr<Controller::IController> platformController =
            std::make_shared<Controller::PlatformController>(platform);
        // Register platformView as Observer to Subject platform
        platform->registerObserver(platformView);
        // TODO - initBounds()
        static int i = 0;
        if (i == 0) {
                platform->setX(Utils::Random::GetRandom(0.f, 8.f));
                platform->setY(Utils::Random::GetRandom(0.f, 14.4f));
        }
        //         TODO - remove
        if (i == 1) {
                platform->setX(Utils::Random::GetRandom(0.f, 8.f));
                platform->setY(Utils::Random::GetRandom(0.f, 14.4f));
        }
        i++;
        return {platform, platformController};
}
std::shared_ptr<Model::Entity> ConcreteFactory::createBackground()
{
        std::shared_ptr<Model::Entity> background = std::make_shared<Model::Background>();
        std::shared_ptr<View::IView> backgroundView = std::make_shared<View::BackgroundView>(background, mWindow);
        background->registerObserver(backgroundView);

        background->setX(1.f);
        background->setY(0.f);

        return background;
}
