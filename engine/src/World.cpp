//
// Created by Pablo Deputter on 18/11/2021.
//

#include "World.h"
#include "util/Stopwatch.h"

using namespace Settings;

World::World(std::shared_ptr<Model::AbstractFactory>& factory, bool playing)
{
        // Initialize factory
        mFactory = factory;
        mActivePlatforms = 0;
        mDifficulty = Settings::eEasy;
        // Initialize Camera settings
        Utils::Camera::getInstance().isMaxHeight(0.f);
        Utils::Camera::getInstance().setWorldDimensions(8.f, 14.4f);
        Utils::Stopwatch::getInstance().mPlayer = mPlayer;
        mPlaying = playing;
}

void World::initWorld()
{
        // Create player
        auto player = mFactory->createPlayer();
        player->setX(Utils::Camera::getInstance().getWorldDimensions().first / 2.f);
        player->setY(4.f);
        mPlayer = player;

        // Create score
        mScore = mFactory->createScore();
        mScore->setX(Utils::Camera::getInstance().getWorldDimensions().first / 2.f);
        mScore->setY(Utils::Camera::getInstance().getWorldDimensions().second - 0.2f);
        // Add to subjects
        Utils::Camera::getInstance().add(mScore);
        mPlayer->add(mScore);

        // Create ground for start
        auto ground = mFactory->createStaticPlatform();
        for (int i = 0; i <= (int)Utils::Camera::getInstance().getWorldDimensions().first;
             i += (int)ground->getWidth()) {
                auto newPlatform = mFactory->createStaticPlatform();
                newPlatform->setX((float)i);
                newPlatform->setY(0.3f);
                newPlatform->setScore(0);
                addEntity(newPlatform);
        }
        ground->onDestroy();

        // Create starting platforms
        const auto temp = CHANCE_BONUS;
        CHANCE_BONUS = 0.f;
        while (mActivePlatforms < MAX_PLATFORMS) {
                generateEntity();
        }
        CHANCE_BONUS = temp;

        // Create Background tiles
        auto bg = mFactory->createBackground();
        const float inverseWidth = Utils::Camera::getInstance().inverseTransform(bg->getWidth(), bg->getHeight()).first;
        const float inverseHeight =
            Utils::Camera::getInstance().getWorldDimensions().second -
            Utils::Camera::getInstance().inverseTransform(bg->getWidth(), bg->getHeight()).second;

        for (float i = 0.f; i < Utils::Camera::getInstance().getWorldDimensions().first; i += inverseWidth) {
                for (float j = Utils::Camera::getInstance().getWorldDimensions().second; j > -2.f; j -= inverseHeight) {
                        auto tile = mFactory->createBackground();
                        tile->setX(i);
                        tile->setY(j);
                        mBackground.emplace_back(tile);
                }
        }
        bg->onDestroy();
}

void World::events(const std::string& move, bool isPressed) const
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
                    Utils::Utilities::checkCollision(mPlayer, i) && mPlayer->getY() < i->getY()) {

                        if (!i->isBonus()) {
                                collided = true;
                        }

                        mPlayer->trigger(EventType::COLLISION, std::make_shared<CollisionEvent>(i, mPlayer));

                        i->trigger(EventType::MOVE, std::make_shared<MoveEvent>(collided));
                        // TODO - leaks
                        //                        i->trigger(EventType::COLLISION, std::make_shared<CollisionEvent>(i,
                        //                        mPlayer));
                        continue;
                }
                i->trigger(EventType::MOVE, std::make_shared<MoveEvent>(false));
        }

        mPlayer->trigger(EventType::MOVE, std::make_shared<MoveEvent>(collided));

        // If Player reached new max. height, Camera can be moved up
        if (Utils::Camera::getInstance().isMaxHeight(mPlayer->getY())) {
                const bool newDifficulty = checkDifficulty();
                if (newDifficulty) {
                        mScore->trigger(EventType::NEW_DIFFICULTY, std::make_shared<NewDifficultyEvent>(mDifficulty));
                }
                // Generate new Entities while active platforms is less than max.
                // platforms required on screen
                while (mActivePlatforms < MAX_PLATFORMS) {
                        generateEntity();
                }
                // Move Camera up
                Utils::Camera::getInstance().move(0.f,
                                                  Utils::Camera::getInstance().getMaxHeight() -
                                                      Utils::Camera::getInstance().getWorldDimensions().second / 2.f);
        }

        // Remove entities that are out of Camera-view or
        // that are not needed anymore
        removeEntities();

        // Player has died
        if (mPlayer->getY() < Utils::Camera::getInstance().getY()) {
                mPlaying = false;
                //                HighScore::getInstance().add(std::make_shared<HighScoreScore>(mScore->getScore(),
                //                                                                              "Name"));
                //                destroy();
        }
}

void World::render() const
{
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

        // Render score
        mScore->trigger(EventType::DRAW, std::make_shared<DrawEvent>());
        //        std::cout << "mPlayer: " << mPlayer->getX() << " : " << mPlayer->getY() << "\n";
}

void World::generateEntity()
{
        // Get height of last added platform
        float lastHeight = mEntities.back()->getY();
        // Max vertical distance between platforms in world
        float verticalRatio = Utils::Camera::getInstance().getWorldDimensions().second / (float)Settings::MAX_PLATFORMS;
        // Calculate max vertical distance when jumped relatively from height of last added entity
        float jumpPeak = lastHeight + (0.195f / 0.005f) * (.195f / 2.f);

        // Get random x-value
        float randX = Utils::Random::getInstance().random(0.f, Utils::Camera::getInstance().getWorldDimensions().first);
        // Get random y-value depending on verticalRatio and height of latest added entity
        float randY = Utils::Random::getInstance().random(lastHeight + (verticalRatio * DIFFICULTY), jumpPeak);

        // Add vertical spacing otherwise, new entities will be placed on top of each other
        if (randY - .50f <= mEntities.back()->getY()) {
                randY += .50f;
        }

        if (CHANCE_BONUS >= Utils::Random::getInstance().random(0.f, 1.f)) {
                spawnBonus(randX, randY);
        } else {
                spawnPlatform(randX, randY);
        }
}

void World::spawnPlatform(float x, float y)
{
        float sum = CHANCE_STATIC + CHANCE_HORIZONTAL + CHANCE_VERTICAL + CHANCE_TEMPORARY;

        // Get random value between [0, 1]
        float rand = Utils::Random::getInstance().random(0.f, sum);

        // Create correct Platform according to randomly generated value
        if (Utils::Utilities::checkWeight(rand, CHANCE_STATIC)) {
                spawnEntity(x, y, Model::eStatic);
        } else if (Utils::Utilities::checkWeight(rand, CHANCE_HORIZONTAL)) {
                spawnEntity(x, y, Model::eHorizontal);
        } else if (Utils::Utilities::checkWeight(rand, CHANCE_VERTICAL)) {
                spawnEntity(x, y, Model::eVertical);
        } else if (Utils::Utilities::checkWeight(rand, CHANCE_TEMPORARY)) {
                spawnEntity(x, y, Model::eTemporary);
        }
        // Dead weight, can sometimes happen
        else {
                spawnEntity(x, y, Model::eStatic);
        }
}

void World::spawnBonus(float x, float y)
{
        float sum = CHANCE_SPRING + CHANCE_JETPACK;

        // Get random value between [0, 1]
        float rand = Utils::Random::getInstance().random(0.f, sum);

        // Create correct Bonus according to randomly generated value
        if (Utils::Utilities::checkWeight(rand, CHANCE_SPRING)) {
                spawnEntity(x, y, Model::eSpring);
        } else if (Utils::Utilities::checkWeight(rand, CHANCE_JETPACK)) {
                spawnEntity(x, y, Model::eJetpack);
        }
        // Dead weight, can sometimes happen
        else {
                spawnEntity(x, y, Model::eSpring);
        }

        // Bonus can only spawn on top of Static Platform, so create new Static Platform
        spawnEntity(x, y - mEntities.back()->getHeight() * 1.5f, Model::eStatic);
}

void World::spawnEntity(float x, float y, Model::Type type)
{
        std::shared_ptr<Model::Entity> entity;

        switch (type) {
        case Model::eStatic:
                entity = mFactory->createStaticPlatform();
                break;
        case Model::eHorizontal:
                entity = mFactory->createHorizontalPlatform();
                break;
        case Model::eVertical:
                entity = mFactory->createVerticalPlatform();
                break;
        case Model::eTemporary:
                entity = mFactory->createTemporaryPlatform();
                break;
        case Model::eJetpack:
                entity = mFactory->createJetpack();
                break;
        case Model::eSpring:
                entity = mFactory->createSpring();
                break;
        case Model::eBackground:
                entity = mFactory->createBackground();
                break;
        }

        if (!entity->isBonus()) {
                mActivePlatforms++;
        }

        entity->setX(x);
        entity->setY(y);
        addEntity(entity);
}

bool World::checkDifficulty()
{
        if (mDifficulty == Settings::Difficulty::eExtreme) {
                return false;
        }

        const float height = Utils::Camera::getInstance().getMaxHeight();
        if (height <= 50.f && mDifficulty != Settings::Difficulty::eEasy) {
                mDifficulty = Settings::Difficulty::eEasy;
                return Settings::setDifficulty(Settings::Difficulty::eEasy);
        } else if (height > 50.f && height <= 150.f && mDifficulty != Settings::Difficulty::eNormal) {
                mDifficulty = Settings::Difficulty::eNormal;
                return Settings::setDifficulty(Settings::Difficulty::eNormal);
        } else if (height > 150.f && height <= 250.f && mDifficulty != Settings::Difficulty::eDifficult) {
                mDifficulty = Settings::Difficulty::eDifficult;
                return Settings::setDifficulty(Settings::Difficulty::eDifficult);
        } else if (height > 250.f && height <= 350.f && mDifficulty != Settings::Difficulty::eHard) {
                mDifficulty = Settings::Difficulty::eHard;
                return Settings::setDifficulty(Settings::Difficulty::eHard);
        } else if (height > 350.f && height <= 450.f && mDifficulty != Settings::Difficulty::eInsane) {
                mDifficulty = Settings::Difficulty::eInsane;
                return Settings::setDifficulty(Settings::Difficulty::eInsane);
        } else if (height > 450.f && height <= 525.f && mDifficulty != Settings::Difficulty::eExtreme) {
                mDifficulty = Settings::Difficulty::eExtreme;
                return Settings::setDifficulty(Settings::Difficulty::eExtreme);
        }
        return false;
}

void World::addEntity(const std::shared_ptr<Model::Entity>& entity) { mEntities.emplace_back(entity); }

void World::removeEntities()
{
        auto it = std::begin(mEntities);
        while (it != std::end(mEntities)) {
                // TODO - jetpack doesn't get destroyed when not used and out of view
                //                if ((*it)->getType() == Model::eJetpack) std::cout << "JETPACK STILL IN PLAY\n";
                if ((*it)->isRemovable()) {
                        if (!(*it)->isBonus()) {
                                mActivePlatforms--;
                        }
                        it = mEntities.erase(it);
                        continue;
                }
                it++;
        }
}

void World::destroy()
{
        std::cout << "worldDestroy\n";
        if (mPlayer == nullptr) {
                std::cout << "null\n";
        }
        mPlayer->onDestroy();
        for (const auto& i : mEntities) {
                i->onDestroy();
        }
        mEntities.clear();
        for (const auto& i : mBackground) {
                i->onDestroy();
        }
        mBackground.clear();
        mScore->onDestroy();
        Utils::Camera::getInstance().reset();
        Utils::Stopwatch::getInstance().reset();
}
