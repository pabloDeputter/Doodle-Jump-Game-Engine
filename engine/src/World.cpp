//
// Created by Pablo Deputter on 18/11/2021.
//

#include "World.h"

World::World(std::shared_ptr<Model::AbstractFactory>& factory)
{
        mFactory = factory;
        mMaxHeight = 0.f;
        Utils::Camera::getInstance().setGameDimensions(8.f, 14.4f);
}

void World::events(const std::string& move, bool isPressed)
{
        // TODO - what check notes
        //        std::cout << Utils::Camera::getInstance().transform(4.f, 5000.f).second << "\n";

        for (auto& i : mControllers) {
                i->onEvent(move, isPressed);
        }
        mPlayerController->onEvent(move, isPressed);
}

void World::update()
{
        bool flagCollision = false;
        for (auto& i : mControllers) {
                if (i->getMEntity()->getType() != Model::ePlayer) {
                        if (std::dynamic_pointer_cast<Model::Player>(mPlayer)->getVelocity().second <= 0 &&
                            Utils::Collision::checkCollision(mPlayer, i->getMEntity()) &&
                            mPlayer->getY() < i->getMEntity()->getY()) {

                                flagCollision = true;
                                mPlayerController->onUpdate(true);
                        }
                        i->onUpdate(false);
                }
        }

        if (flagCollision)
                return;
        mPlayerController->onUpdate(false);
}

void World::render()
{

        //        auto plat = mFactory->createStaticPlatform();
        //        plat.first->setX(4.f);
        //        plat.first->setY(mPlayer->getY() + 1.4f);
        //        World::addEntity(plat);

        auto& cc = Utils::Camera::getInstance();
        if (mPlayer->getY() > mMaxHeight) {
                mMaxHeight = mPlayer->getY();
                cc.move(0.f, mMaxHeight - cc.getGameDimensions().second / 2.f);
        }

        auto itBackground = mBackground.begin();
        while (itBackground != mBackground.end()) {
                if ((*itBackground)->getY() < cc.getY()) {
                        std::cout << "bgOutOfView"
                                  << "\n";
                        (*itBackground)->triggerObserver();
                        itBackground = mBackground.erase(itBackground);
                        continue;
                }
                (*itBackground)->triggerObserver();
                itBackground++;
        }

        // TODO - check if in view

        // TODO - animation
        mPlayer->triggerObserver();

        std::vector<bool> toRemove;
        for (auto& i : mEntities) {

                if (i->getY() < cc.getY()) {
                        toRemove.emplace_back(true);
                } else {
                        toRemove.emplace_back(false);
                }

                // All observers are removed from subject
                i->triggerObserver();
        }

        //        auto i = std::begin(V);
        //        while (i != std::end(V)) {
        //                if (toRemove.find(*i) != toRemove.end()) {
        //                        delete (*i);
        //                        i = V.erase(i);
        //                }
        //                else i++;
        //        }

        auto itController = std::begin(mControllers);
        auto itEntity = std::begin(mEntities);

        for (int i = 0; i < toRemove.size(); i++) {
                if (toRemove[i]) {
                        itController = mControllers.erase(itController);
                        itEntity = mEntities.erase(itEntity);
                }
        }
}

void World::addEntity(
    const std::pair<std::shared_ptr<Model::Entity>, const std::shared_ptr<Controller::IController>>& entity)
{
        mEntities.emplace_back(entity.first);
        mControllers.emplace_back(entity.second);
        //        std::cout << mEntities.size() << "\n";
}

void World::addBackground(const std::shared_ptr<Model::Entity>& entity) { mBackground.emplace_back(entity); }

void World::addPlayer(
    const std::pair<std::shared_ptr<Model::Entity>, const std::shared_ptr<Controller::IController>>& entity)
{
        mPlayer = entity.first;
        mPlayerController = entity.second;
}

void World::initializeWorld()
{

        auto plat = mFactory->createStaticPlatform();
        plat.first->setX(4.f);
        plat.first->setY(1.4f);
        World::addEntity(plat);

        ////        for (int i = 0; i < 5000; i++) {
        ////                auto plat = mFactory->createStaticPlatform();
        ////                plat.first->setX(4.f);
        ////                plat.first->setY(-11.f);
        ////                World::addEntity(plat);
        ////        }
        //

        auto bg = mFactory->createBackground();

        float width = bg->getWidth();
        float height = bg->getHeight();

        // TODO - remove
        bg->onInvisible();

        auto& cc = Utils::Camera::getInstance();

        //        auto a = cc.transform(2.f, 2.f);
        //        std::cout << a.first << " : " << a.second << "\n";

        //        auto b = cc.inverseTransform(a.first, a.second);
        //        std::cout << b.first << " : " << b.second << "\n";

        float width_ = Utils::Camera::getInstance().inverseTransform(width, height).first;
        float height_ = Utils::Camera::getInstance().inverseTransform(width, height).second;
        height_ = Utils::Camera::getInstance().getGameDimensions().second - height_;

        size_t counter = 0;
        for (float i = 0.f; i < Utils::Camera::getInstance().getGameDimensions().first; i += width_) {
                for (float j = Utils::Camera::getInstance().getGameDimensions().second; j > 0; j -= height_) {
                        auto n = mFactory->createBackground();
                        n->setX(i);
                        n->setY(j);
                        mBackground.emplace_back(n);
                        counter++;
                }
        }

        //
        //                auto platform = mFactory->createPlatform().first;
        //
        //                auto dim = Utils::Camera::getInstance().inverseTransform(platform->getWidth(),
        //                platform->getHeight());
        //
        //                for (float i = 0.f; i < Utils::Camera::getInstance().getGameDimensions().first; i +=
        //                dim.first) {
        //                        auto n = mFactory->createStaticPlatform();
        //                        n.first->setX(i);
        //                        n.first->setY(Utils::Camera::getInstance().getGameDimensions().second);
        //                        World::addEntity(n);
        //                }
}
