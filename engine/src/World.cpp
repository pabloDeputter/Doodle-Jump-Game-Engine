//
// Created by Pablo Deputter on 18/11/2021.
//

#include "World.h"

World::World(std::shared_ptr<Model::AbstractFactory>& factory)
{
        mFactory = factory;

        Utils::Camera::getInstance().isMaxHeight(0.f);
        Utils::Camera::getInstance().setWorldDimensions(8.f, 14.4f);
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
        bool flagCollision = false;
        for (auto& i : mControllers) {
                if (i->getMEntity()->getType() != Model::ePlayer) {
                        if (std::dynamic_pointer_cast<Model::Player>(mPlayer)->getVelocity().second <= 0 &&
                            Utils::Collision::checkCollision(mPlayer, i->getMEntity()) &&
                            mPlayer->getY() < i->getMEntity()->getY()) {

                                flagCollision = true;
                                mPlayerController->onUpdate(true);
                        }
                        i->onUpdate(true);
                }
        }

        if (flagCollision)
                return;
        mPlayerController->onUpdate(false);

        // AND IS MOVING LEFT...
        if (mPlayer->getX() < 0.f) {
                mPlayer->setX(8.f);
        }
        if (mPlayer->getX() > 8.f) {
                mPlayer->setX(0.f);
        }
}

void World::render()
{
        //         Kan ook random gedaan worden
        static float heightHarndess = 50.f;
        static float hardness = 0.05f;

        if (Utils::Camera::getInstance().getMaxHeight() > heightHarndess) {
                heightHarndess += 50.f;
                hardness -= 0.007f;
        }

        //                auto plat = mFactory->createStaticPlatform();
        //                plat.first->setX(4.f);
        //                plat.first->setY(mPlayer->getY() + 1.4f);
        //                World::addEntity(plat);

        auto& cc = Utils::Camera::getInstance();
        if (Utils::Camera::getInstance().isMaxHeight(mPlayer->getY())) {

                if (std::dynamic_pointer_cast<Model::Player>(mPlayer)->getVelocity().second <= hardness) {
                        // Add new? hier?? - enkel als moving up
                        World::generate();
                }

                // TODO - mCameraX is altijd 7.2 (helft van game world y) onder mMaxHeight
                cc.move(0.f, Utils::Camera::getInstance().getMaxHeight() - cc.getWorldDimensions().second / 2.f);
                //                std::cout << "mMaxHeight: " << Utils::Camera::getInstance().getMaxHeight() << "\n";
                //                std::cout << "mCameraX: " << Utils::Camera::getInstance().getY() << "\n";
        }

        auto itBackground = mBackground.begin();
        while (itBackground != mBackground.end()) {
                if ((*itBackground)->getY() < cc.getY()) {
                        (*itBackground)->setY((*itBackground)->getY() + cc.getWorldDimensions().second + 2.f);
                        //                        (*itBackground)->trigger();
                        //                        itBackground = mBackground.erase(itBackground);
                        //                        continue;
                }
                (*itBackground)->trigger();
                itBackground++;
        }

        // TODO - check if in view

        // TODO - animation
        mPlayer->trigger();

        std::vector<bool> toRemove;
        for (auto& i : mEntities) {

                if (i->getY() < cc.getY()) {
                        toRemove.emplace_back(true);
                } else {
                        toRemove.emplace_back(false);
                }

                // All observers are removed from subject
                i->trigger();
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
        auto plat = mFactory->createStaticPlatform();
        plat.first->setX(3.f);
        plat.first->setY(1.5f);
        World::addEntity(plat);

        for (int i = 0; i < (int)Utils::Random::getInstance().GetRandom(3, 15); i++) {
                auto plat = mFactory->createStaticPlatform();
                float randX = Utils::Random::GetRandom(0.f, Utils::Camera::getInstance().getWorldDimensions().first);
                float randY = Utils::Random::GetRandom(0.f, Utils::Camera::getInstance().getWorldDimensions().second);
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
        height_ = Utils::Camera::getInstance().getWorldDimensions().second - height_;

        size_t counter = 0;
        for (float i = 0.f; i < Utils::Camera::getInstance().getWorldDimensions().first; i += width_) {
                for (float j = Utils::Camera::getInstance().getWorldDimensions().second; j > -14.4f; j -= height_) {
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
        //                for (float i = 0.f; i < Utils::Camera::getInstance().getWorldDimensions().first; i +=
        //                dim.first) {
        //                        auto n = mFactory->createStaticPlatform();
        //                        n.first->setX(i);
        //                        n.first->setY(Utils::Camera::getInstance().getWorldDimensions().second);
        //                        World::addEntity(n);
        //                }
}

void World::generate()
{

        // Moet jump halen
        // Jump height + x waarde van player (vector) naar nieuwe platform moet groot genoeg zijn
        // elke zoveel y-waarde gaat kans op speciaal platform naar boven + minder platformen
        // platformen niet zo dicht bij kant zetten
        // mag een max aantal platforms maar bestaan

        float t = .25f / .006f;
        float peak = mPlayer->getY() + t * .25f / 2.f;

        float randX = Utils::Random::GetRandom(0.f, Utils::Camera::getInstance().getWorldDimensions().first);
        float randY = Utils::Random::GetRandom(0.f, peak);

        auto platform = mFactory->createPlatform();

        platform.first->setX(randX);
        platform.first->setY(Utils::Camera::getInstance().getMaxHeight() +
                             Utils::Camera::getInstance().getWorldDimensions().second / 2.f + randY);

        //        std::cout << platform.first->getY() << "\n";

        float magnitude = sqrt(std::pow((randX - mPlayer->getX()), 2.f) + std::pow((randY - mPlayer->getY()), 2.f));

        //        std::cout << magnitude << "\n";

        addEntity(platform);
}
