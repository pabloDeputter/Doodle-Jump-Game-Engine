//
// Created by Pablo Deputter on 18/11/2021.
//

#include "World.h"

World::World(std::shared_ptr<Model::AbstractFactory>& factory)
{
        mFactory = factory;
        // TODO - EVENTS
        mScore = std::make_shared<Score>();

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
        std::vector<bool> toRemove;
        for (auto& i : mControllers) {
                if (i->getEntity()->getType() != Model::ePlayer) {
                        if (std::dynamic_pointer_cast<Model::Player>(mPlayer)->getVelocity().second <= 0 &&
                            Utils::Collision::checkCollision(mPlayer, i->getEntity()) &&
                            mPlayer->getY() < i->getEntity()->getY()) {

                                flagCollision = true;
                                mPlayerController->onUpdate(true);

                                if (i->getEntity()->getType() == Model::eTemporary) {
                                        i->onUpdate(true);
                                        toRemove.emplace_back(true);
                                        continue;
                                }

                                if (i->getEntity()->getType() == Model::eJetpack) {
                                        std::cout << "jetpack\n";
                                        mPlayer->accept(i->getEntity());
                                        i->onUpdate(true);
                                        toRemove.emplace_back(false);
                                        i->getEntity()->setRemoveFlag(true);
                                        continue;
                                }
                                // TODO - Model::eBonus
                                if (i->getEntity()->getType() == Model::eSpring) {
                                        std::cout << "spring\n";
                                        mPlayer->accept(i->getEntity());
                                        i->onUpdate(true);
                                        toRemove.emplace_back(true);
                                        i->getEntity()->setRemoveFlag(true);
                                        continue;
                                }
                        }
                }
                i->onUpdate(false);
                toRemove.emplace_back(false);
        }
        // REMOVE FLAG????

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

        //        //         Kan ook random gedaan worden
        //        static float heightHarndess = 50.f;
        //        static float hardness = 0.02f;
        //
        //        if (Utils::Camera::getInstance().getMaxHeight() > heightHarndess) {
        //                heightHarndess += 50.f;
        //                hardness -= 0.007f;
        //        }

        unsigned int maxPlatforms = 15;
        //        std::cout << "maxHeight: " << Utils::Camera::getInstance().getMaxHeight() << "\n";
        auto& cc = Utils::Camera::getInstance();
        //        std::cout << cc.getMaxHeight() << "\n";
        if (Utils::Camera::getInstance().isMaxHeight(mPlayer->getY())) {

                //                std::cout << "new maxHeight: " << Utils::Camera::getInstance().getMaxHeight() << "\n";

                //                if (mEntities.size() < maxPlatforms)
                //                {
                //                        World::generate();
                //                }

                if (mEntities.size() < maxPlatforms) {
                        //                        std::cout << "lol\n";
                        // Add new? hier?? - enkel als moving up
                        World::generate();
                }

                cc.move(0.f, Utils::Camera::getInstance().getMaxHeight() - (cc.getWorldDimensions().second / 2.f));
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

                        if (i->getRemovable() && i->getType() == Model::eJetpack) {

                                if (i->isRemovable()) {
                                        mPlayer->accept(i);
                                        toRemove.emplace_back(true);
                                } else
                                        toRemove.emplace_back(false);
                        }

                        else
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
        // Create player
        auto player = mFactory->createPlayer();
        player.first->setX(Utils::Camera::getInstance().getWorldDimensions().first / 2.f);
        player.first->setY(2.f);
        addPlayer(player);

        // Create ground
        auto ground = mFactory->createStaticPlatform().first;
        for (int i = 0; i <= (int)Utils::Camera::getInstance().getWorldDimensions().first;
             i += (int)ground->getWidth()) {
                auto newPlatform = mFactory->createStaticPlatform();
                newPlatform.first->setX((float)i);
                newPlatform.first->setY(0.3f);
                addEntity(newPlatform);
        }
        ground->onDestroy();

        // Create random number of static starting platforms between 8 and 15
        for (int i = 0; i < (int)Utils::Random::getInstance().random(8, 15); i++) {
                auto newPlatform = mFactory->createStaticPlatform();
                float randX =
                    Utils::Random::getInstance().random(0.f, Utils::Camera::getInstance().getWorldDimensions().first);
                float randY = Utils::Random::getInstance().random(
                    mEntities.back()->getY(), mEntities.back()->getY() + (.21f / 0.006f) * (.21f / 2.f));

                if (randY - .50f <= mEntities.back()->getY()) {
                        randY += .50f;
                }

                newPlatform.first->setX(randX);
                newPlatform.first->setY(randY);
                addEntity(newPlatform);
        }

        // Create background
        auto bg = mFactory->createBackground();
        const float inverseWidth = Utils::Camera::getInstance().inverseTransform(bg->getWidth(), bg->getHeight()).first;
        const float inverseHeight =
            Utils::Camera::getInstance().getWorldDimensions().second -
            Utils::Camera::getInstance().inverseTransform(bg->getWidth(), bg->getHeight()).second;

        for (float i = 0.f; i < Utils::Camera::getInstance().getWorldDimensions().first; i += inverseWidth) {
                for (float j = Utils::Camera::getInstance().getWorldDimensions().second; j > -2.f; j -= inverseHeight) {
                        auto n = mFactory->createBackground();
                        n->setX(i);
                        n->setY(j);
                        mBackground.emplace_back(n);
                }
        }
        bg->onDestroy();
}

void World::generate()
{
        // TODO magnitude???
        auto newPlatform = mFactory->createStaticPlatform();
        auto newBonus = mFactory->createJetpack();

        float jumpPeak = mEntities.back()->getY() + (.21f / 0.006f) * (.21f / 2.f);

        float randX = Utils::Random::getInstance().random(0.f, Utils::Camera::getInstance().getWorldDimensions().first);
        float randY = Utils::Random::getInstance().random(mEntities.back()->getY(), jumpPeak);

        // Otherwise, new platforms will be placed on top of each other
        if (randY - .50f <= mEntities.back()->getY()) {
                randY += .50f;
        }

        newPlatform.first->setX(randX);
        newPlatform.first->setY(randY);
        newBonus.first->setX(randX - newPlatform.first->getWidth() / 2.f);
        newBonus.first->setY(randY + 0.6f);

        addEntity(newPlatform);
        addEntity(newBonus);
}
