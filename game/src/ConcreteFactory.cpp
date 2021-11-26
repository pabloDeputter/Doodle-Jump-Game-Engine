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
        return std::make_pair(player, playerController);
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
                platform->setX(200);
                platform->setY(1400);
        }
        // TODO - remove
        //        if (i == 1) {
        //                platform->setX(400);
        //                platform->setY(720);
        //        }
        //        i++;
        return std::make_pair(platform, platformController);
}
