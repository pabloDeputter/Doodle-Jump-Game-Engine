//
// Created by Pablo Deputter on 18/11/2021.
//

#include "World.h"

World::World(std::shared_ptr<Model::AbstractFactory>& factory)
{
        mFactory = factory;

        Utils::Camera::getInstance().isMaxHeight(0.f);
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

        //        // AND IS MOVING LEFT...
        //        if (mPlayer->getX() < 0.f)
        //        {
        //                mPlayer->setX(8.f);
        //        }
        //        if (mPlayer->getX() > 8.f)
        //        {
        //                mPlayer->setX(0.f);
        //        }
}

void World::render()
{
        // Kan ook random gedaan worden
        static float heightHarndess = 50.f;
        static float hardness = 0.05f;

        if (Utils::Camera::getInstance().getMaxHeight() > heightHarndess) {
                heightHarndess += 50.f;
                hardness -= 0.007f;
        }

        //        auto plat = mFactory->createStaticPlatform();
        //        plat.first->setX(4.f);
        //        plat.first->setY(mPlayer->getY() + 1.4f);
        //        World::addEntity(plat);

        auto& cc = Utils::Camera::getInstance();
        if (Utils::Camera::getInstance().isMaxHeight(mPlayer->getY())) {

                if (std::dynamic_pointer_cast<Model::Player>(mPlayer)->getVelocity().second <= hardness) {
                        // Add new? hier?? - enkel als moving up
                        World::generate();
                }

                // TODO - mCameraX is altijd 7.2 (helft van game world y) onder mMaxHeight
                cc.move(0.f, Utils::Camera::getInstance().getMaxHeight() - cc.getGameDimensions().second / 2.f);
                std::cout << "mMaxHeight: " << Utils::Camera::getInstance().getMaxHeight() << "\n";
                std::cout << "mCameraX: " << Utils::Camera::getInstance().getY() << "\n";
        }

        auto itBackground = mBackground.begin();
        while (itBackground != mBackground.end()) {
                if ((*itBackground)->getY() < cc.getY()) {
                        (*itBackground)->setY((*itBackground)->getY() + cc.getGameDimensions().second + 2.f);
                        //                        (*itBackground)->triggerObserver();
                        //                        itBackground = mBackground.erase(itBackground);
                        //                        continue;
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

        auto itController = std::begin(mControllers);
        auto itEntity = std::begin(mEntities);

        for (int i = 0; i < toRemove.size(); i++) {
                if (toRemove[i]) {
                        itController = mControllers.erase(itController);
                        itEntity = mEntities.erase(itEntity);
                        continue;
                }
                itController++;
                itEntity++;
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

        for (int i = 0; i < (int)Utils::Random::GetInstance().GetRandom(3, 15); i++) {
                auto plat = mFactory->createStaticPlatform();
                float randX = Utils::Random::GetRandom(0.f, Utils::Camera::getInstance().getGameDimensions().first);
                float randY = Utils::Random::GetRandom(0.f, Utils::Camera::getInstance().getGameDimensions().second);
                plat.first->setX(randX);
                plat.first->setY(randY);
                World::addEntity(plat);
        }

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

        float width_ = Utils::Camera::getInstance().inverseTransform(width, height).first;
        float height_ = Utils::Camera::getInstance().inverseTransform(width, height).second;
        height_ = Utils::Camera::getInstance().getGameDimensions().second - height_;

        size_t counter = 0;
        for (float i = 0.f; i < Utils::Camera::getInstance().getGameDimensions().first; i += width_) {
                for (float j = Utils::Camera::getInstance().getGameDimensions().second; j > -14.4f; j -= height_) {
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

void World::generate()
{

        //        std::cout << mEntities.size() << "\n";
        // Moet jump halen
        // Jump height + x waarde van player (vector) naar nieuwe platform moet groot genoeg zijn
        // elke zoveel y-waarde gaat kans op speciaal platform naar boven + minder platformen
        // platformen niet zo dicht bij kant zetten

        float randX = Utils::Random::GetRandom(0.f, Utils::Camera::getInstance().getGameDimensions().first);
        float randY = Utils::Random::GetRandom(0.f, Utils::Camera::getInstance().getGameDimensions().second);

        auto platform = mFactory->createPlatform();

        platform.first->setX(randX);
        platform.first->setY(Utils::Camera::getInstance().getMaxHeight() +
                             Utils::Camera::getInstance().getGameDimensions().second / 2.f + randY);

        //        std::cout << platform.first->getY() << "\n";

        addEntity(platform);
}
