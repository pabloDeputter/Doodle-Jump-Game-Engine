//
// Created by Pablo Deputter on 18/11/2021.
//

#include "World.h"

World::World(std::shared_ptr<Model::AbstractFactory>& factory)
{
        mFactory = factory;

        // Initialize Camera settings
        Utils::Camera::getInstance().isMaxHeight(0.f);
        Utils::Camera::getInstance().setWorldDimensions(8.f, 14.4f);

        Utils::Stopwatch::getInstance().mPlayer = mPlayer;
}

void World::events(const std::string& move, bool isPressed)
{
        for (const auto& i : mEntities) {
                i->trigger(EventType::KEY_PRESSED, std::make_shared<KeyPressedEvent>(move, isPressed));
        }
        mPlayer->trigger(EventType::KEY_PRESSED, std::make_shared<KeyPressedEvent>(move, isPressed));
}

void World::update()
{

        // TODO - cleanup lil bit
        // TODO - remove entities??
        // TODO - collision playerController
        bool collided = false;
        for (auto& i : mEntities) {
                if (std::dynamic_pointer_cast<Model::Player>(mPlayer)->getVelocity().second <= 0 &&
                    Utils::Collision::checkCollision(mPlayer, i) && mPlayer->getY() < i->getY()) {

                        if (!i->isBonus()) {
                                collided = true;
                        }

                        mPlayer->trigger(EventType::COLLISION, std::make_shared<CollisionEvent>(i, mPlayer));

                        i->trigger(EventType::MOVE, std::make_shared<MoveEvent>(collided));
                        continue;
                }
                i->trigger(EventType::MOVE, std::make_shared<MoveEvent>(false));
        }

        mPlayer->trigger(EventType::MOVE, std::make_shared<MoveEvent>(collided));

        //
        //
        //
        //
        //        bool flagCollision = false;
        //        std::vector<bool> toRemove;
        //        for (auto& i : mControllers) {
        //                if (i->getEntity()->getType() != Model::ePlayer) {
        //                        if (std::dynamic_pointer_cast<Model::Player>(mPlayer)->getVelocity().second <= 0 &&
        //                            Utils::Collision::checkCollision(mPlayer, i->getEntity()) &&
        //                            mPlayer->getY() < i->getEntity()->getY()) {
        //
        //
        //
        //
        //                                flagCollision = true;
        //                                mPlayerController->onUpdate(true);
        //
        //
        //                                if (i->getEntity()->getType() == Model::eTemporary) {
        //                                        i->onUpdate(true);
        //                                        toRemove.emplace_back(true);
        //                                        continue;
        //                                }
        //
        //                                if (i->getEntity()->getType() == Model::eJetpack) {
        //                                        std::cout << "jetpack\n";
        //                                        mPlayer->accept(i->getEntity());
        //                                        i->onUpdate(true);
        //                                        toRemove.emplace_back(false);
        //                                        i->getEntity()->setRemoveFlag(true);
        //                                        continue;
        //                                }
        //                                // TODO - Model::eBonus
        //                                if (i->getEntity()->getType() == Model::eSpring) {
        //                                        std::cout << "spring\n";
        //                                        mPlayer->accept(i->getEntity());
        //                                        i->onUpdate(true);
        //                                        toRemove.emplace_back(true);
        //                                        i->getEntity()->setRemoveFlag(true);
        //                                        continue;
        //                                }
        //                        }
        //                }
        //                i->onUpdate(false);
        //                toRemove.emplace_back(false);
        //        }
        //        // REMOVE FLAG????
        //        if (flagCollision)
        //                return;
        //        mPlayerController->onUpdate(false);
}

void World::render()
{
        removeEntities();

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
                        // Add new? hier?? - enkel als moving up
                        World::generate();
                }

                cc.move(0.f, Utils::Camera::getInstance().getMaxHeight() - (cc.getWorldDimensions().second / 2.f));
        }

        // Render background
        for (const auto& i : mBackground) {
                if (i->getY() < Utils::Camera::getInstance().getY()) {
                        i->trigger(EventType::OUT_OF_VIEW, std::make_shared<OutOfViewEvent>());
                }
                i->trigger(EventType::DRAW, std::make_shared<DrawEvent>());
        }

        // Render entities
        for (const auto& i : mEntities) {
                i->trigger(EventType::DRAW, std::make_shared<DrawEvent>());
        }

        // TODO - animation
        // Render player
        mPlayer->trigger(EventType::DRAW, std::make_shared<DrawEvent>());
}

void World::addEntity(const std::shared_ptr<Model::Entity>& entity) { mEntities.emplace_back(entity); }

void World::addBackground(const std::shared_ptr<Model::Entity>& entity) { mBackground.emplace_back(entity); }

void World::addPlayer(const std::shared_ptr<Model::Player>& player) { mPlayer = player; }

void World::initializeWorld()
{
        // Create player
        auto player = mFactory->createPlayer();
        player->setX(Utils::Camera::getInstance().getWorldDimensions().first / 2.f);
        player->setY(2.f);
        addPlayer(player);

        // Create score
        mScore = std::make_shared<Score>();
        // Add to subjects
        Utils::Camera::getInstance().add(mScore);
        mPlayer->add(mScore);

        // Create ground
        auto ground = mFactory->createStaticPlatform();
        for (int i = 0; i <= (int)Utils::Camera::getInstance().getWorldDimensions().first;
             i += (int)ground->getWidth()) {
                auto newPlatform = mFactory->createStaticPlatform();
                newPlatform->setX((float)i);
                newPlatform->setY(0.3f);
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

                newPlatform->setX(randX);
                newPlatform->setY(randY);
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
        //        auto newBonus = mFactory->createJetpack();

        float jumpPeak = mEntities.back()->getY() + (.21f / 0.006f) * (.21f / 2.f);

        float randX = Utils::Random::getInstance().random(0.f, Utils::Camera::getInstance().getWorldDimensions().first);
        float randY = Utils::Random::getInstance().random(mEntities.back()->getY(), jumpPeak);

        // Otherwise, new platforms will be placed on top of each other
        if (randY - .50f <= mEntities.back()->getY()) {
                randY += .50f;
        }

        newPlatform->setX(randX);
        newPlatform->setY(randY);
        //        newBonus->setX(randX - newPlatform->getWidth() / 2.f);
        //        newBonus->setY(randY + 0.6f);

        addEntity(newPlatform);
        //        addEntity(newBonus);
}

void World::removeEntities()
{
        auto it = std::begin(mEntities);
        while (it != std::end(mEntities)) {
                if ((*it)->isRemovable()) {
                        it = mEntities.erase(it);
                        continue;
                }
                it++;
        }
}