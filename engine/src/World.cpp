//
// Created by Pablo Deputter on 18/11/2021.
//

#include "World.h"

World::World() { Utils::Camera::getInstance().setGameDimensions(8.f, 14.4f); }

void World::events(const std::string& move, bool isPressed)
{
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
                        if (std::dynamic_pointer_cast<Model::Player>(mPlayer)->getVelocity().second >= 0 &&
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
        // TODO - animation
        mPlayer->triggerObserver();
        for (auto& i : mEntities) {
                i->triggerObserver();
        }
}

void World::addEntity(
    const std::pair<std::shared_ptr<Model::Entity>, const std::shared_ptr<Controller::IController>>& entity)
{
        mEntities.emplace_back(entity.first);
        mControllers.emplace_back(entity.second);
}

void World::addPlayer(
    const std::pair<std::shared_ptr<Model::Entity>, const std::shared_ptr<Controller::IController>>& entity)
{
        mPlayer = entity.first;
        mPlayerController = entity.second;
}