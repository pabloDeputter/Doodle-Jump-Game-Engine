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
        for (auto& i : mControllers) {
                i->onEvent(move, isPressed);
        }
        mPlayerController->onEvent(move, isPressed);
}

void World::update()
{
        //        bool flagCollision = false;
        //        for (auto& i : mControllers) {
        //                if (i->getMEntity()->getType() != Model::ePlayer) {
        //                        if (std::dynamic_pointer_cast<Model::Player>(mPlayer)->getVelocity().second >= 0 &&
        //                            Utils::Collision::checkCollision(mPlayer, i->getMEntity()) &&
        //                            mPlayer->getY() < i->getMEntity()->getY()) {
        //
        //                                flagCollision = true;
        //                                mPlayerController->onUpdate(true);
        //                        }
        //                        i->onUpdate(false);
        //                }
        //        }
        //
        //        if (flagCollision)
        //                return;
        //        mPlayerController->onUpdate(false);
}

void World::render()
{
        //        std::cout << "mMplayer->getY(): " << mPlayer->getY() << "\n";
        //        std::cout << "mMaxHeight: " << mMaxHeight << "\n";
        //        // TODO - edit
        //        if (mPlayer->getY() > mMaxHeight) {
        //                mMaxHeight = mPlayer->getY();
        //                Utils::Camera::getInstance().move(Utils::Camera::getInstance().getGameDimensiosn().first
        //                / 2.f,
        //                                                  (-mMaxHeight));
        //        }
        //
        //
        //        std::cout << Utils::Camera::getInstance().getPosition().first << " : " <<
        //        Utils::Camera::getInstance().getPosition().second << "\n";

        //        for (auto& i : mBackground) {
        //                i->triggerObserver();
        //        }

        // TODO - animation
        mPlayer->triggerObserver();
        //        for (auto& i : mEntities) {
        //                i->triggerObserver();
        //        }
}

void World::addEntity(
    const std::pair<std::shared_ptr<Model::Entity>, const std::shared_ptr<Controller::IController>>& entity)
{
        mEntities.emplace_back(entity.first);
        mControllers.emplace_back(entity.second);
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
        //
        //        //        World::addPlayer(mFactory->createPlayer());
        //
        //        auto bg = mFactory->createBackground();
        //
        //        float width = bg->getWidth();
        //        float height = bg->getHeight();
        //
        //        float width_ = Utils::Camera::getInstance().inverseTransform(width, height).first;
        //        float height_ = Utils::Camera::getInstance().inverseTransform(width, height).second;
        //
        //        //        std::cout << width_ << " : " << height_ << "\n";
        //
        //        for (float i = 0.f; i < Utils::Camera::getInstance().getGameDimensiosn().first; i += width_) {
        //                for (float j = 0.f; j < Utils::Camera::getInstance().getGameDimensiosn().second; j += height_)
        //                {
        //                        auto n = mFactory->createBackground();
        //                        n->setX(i);
        //                        n->setY(j);
        //                        mBackground.emplace_back(n);
        //                }
        //        }
        //
        //        auto platform = mFactory->createPlatform().first;
        //
        //        auto dim = Utils::Camera::getInstance().inverseTransform(platform->getWidth(), platform->getHeight());
        //
        //        for (float i = 0.f; i < Utils::Camera::getInstance().getGameDimensiosn().first; i += dim.first) {
        //                auto n = mFactory->createStaticPlatform();
        //                n.first->setX(i);
        //                n.first->setY(Utils::Camera::getInstance().getGameDimensiosn().second);
        //                World::addEntity(n);
        //        }
}
