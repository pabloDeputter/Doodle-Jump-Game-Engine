//
// Created by Pablo Deputter on 18/11/2021.
//

#include "World.h"
#include "util/Stopwatch.h"

using namespace Settings;

World::World(std::shared_ptr<Factory::AbstractFactory>& factory, bool playing, Settings::Difficulty diff)
{
        // Initialize factory
        mFactory = factory;
        mActivePlatforms = 0;
        // Initialize starter settings
        mDifficulty = diff;
        setDifficulty(diff);
        // Initialize Camera settings
        Utils::Camera::getInstance().isMaxHeight(0.f);
        // Default World dimensions
        Utils::Camera::getInstance().setWorldDimensions(
            Utils::Camera::getInstance().getWindowDimensions().first / 100.f,
            Utils::Camera::getInstance().getWindowDimensions().second / 100.f);
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
        for (float i = 0; i <= (float)Utils::Camera::getInstance().getWorldDimensions().first;
             i += (float)ground->getWidth() / 2.f) {
                auto newPlatform = mFactory->createStaticPlatform();
                newPlatform->setX((float)i);
                newPlatform->setY(0.2f);
                newPlatform->setScore(0);
                addEntity(newPlatform);
        }
        ground->onDestroy();

        // Create starting platforms
        while (mActivePlatforms < MAX_PLATFORMS) {
                generateEntity();
        }

        // Create Background tiles
        auto bg = mFactory->createBackground();
        // Fill World with Background tiles
        for (float i = 0.f; i < Utils::Camera::getInstance().getWorldDimensions().first; i += bg->getWidth()) {
                for (float j = Utils::Camera::getInstance().getWorldDimensions().second; j > -2.f;
                     j -= bg->getHeight()) {
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
        // Traverse entities and trigger KEY_PRESSED event towards registered observers
        for (const auto& i : mEntities) {
                i->trigger(EventType::KEY_PRESSED, std::make_shared<KeyPressedEvent>(move, isPressed));
        }
        mPlayer->trigger(EventType::KEY_PRESSED, std::make_shared<KeyPressedEvent>(move, isPressed));
}

void World::update()
{
        // Remove entities that are out of Camera-view or that are not needed anymore
        removeEntities();
        bool collided = false;
        // Travers active entities
        for (const auto& i : mEntities) {
                // If player vertical velocity is less than or equal to 0 AND there is collision between
                // the given Entity and the Player --> Player has valid collision
                if (mPlayer->getVelocity().second <= 0 && Utils::Utilities::checkCollision(mPlayer, i)) {

                        if (!i->isBonus()) {
                                collided = true;
                        }
                        mPlayer->trigger(EventType::COLLISION, std::make_shared<CollisionEvent>(i, mPlayer));

                        // Move Entity with event payload that there was a collision between Entity and Player
                        i->trigger(EventType::MOVE, std::make_shared<MoveEvent>(collided));
                }
                // If there is no collision between Entity and Player we just move the Entity
                else {
                        i->trigger(EventType::MOVE, std::make_shared<MoveEvent>(false));
                }
        }
        // Trigger MoveEvent towards Players observers (Controller,View)
        mPlayer->trigger(EventType::MOVE, std::make_shared<MoveEvent>(collided));

        // If Player reached new max. height, Camera can be moved up.
        if (Utils::Camera::getInstance().isMaxHeight(mPlayer->getY())) {
                // Check if we reached a new level / difficulty
                const bool newDifficulty = checkDifficulty();
                // If we reached a new difficulty we trigger a NewDifficultyEvent towards Score's observers (View)
                if (newDifficulty) {
                        mScore->trigger(EventType::NEW_DIFFICULTY, std::make_shared<NewDifficultyEvent>(mDifficulty));
                }
                // Move Camera up
                Utils::Camera::getInstance().move(0.f,
                                                  Utils::Camera::getInstance().getMaxHeight() -
                                                      Utils::Camera::getInstance().getWorldDimensions().second / 2.f);

                // Keep on generating new Bonuses or Platforms while there are less active platforms in the world
                // that are required for the current difficulty
                while (mActivePlatforms < MAX_PLATFORMS) {
                        generateEntity();
                }
        }
        // Remove entities that are out of Camera-view or that are not needed anymore
        removeEntities();
        // If Player is out of view from the Camera it has died, so the game is over.
        if (mPlayer->isOutOfView()) {
                mPlaying = false;
        }
}

void World::render() const
{
        // Render background
        for (const auto& i : mBackground) {
                // If Background tile is out of view it will be moved up and will be moved the screensize (
                // in world coordinates) up, so it gets automatically recycled as the Player moves up
                if (i->isOutOfView()) {
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
}

void World::generateEntity()
{
        // Get height of last added platform
        float lastHeight = mEntities.back()->getY();
        // Max vertical distance between two platforms, so it can fill up the whole screen
        float verticalRatio = Utils::Camera::getInstance().getWorldDimensions().second / (float)Settings::MAX_PLATFORMS;
        // Calculate max vertical distance when jumped relatively from height of last added entity
        float jumpPeak = lastHeight + (0.195f / 0.005f) * (.195f / 2.f);

        // Get random x-value
        float randX = Utils::Random::getInstance().random(0.f, Utils::Camera::getInstance().getWorldDimensions().first);
        // Get random y-value between height of last added entity and jumpPeak. We multiply
        // lastHeight with verticalRatio and the DIFFICULTY factor so platforms will be placed
        // harder as Player moves up in the World.
        float randY = Utils::Random::getInstance().random(lastHeight + (verticalRatio * DIFFICULTY), jumpPeak);

        // Add vertical spacing otherwise, new entities will be placed on top of each other
        if (randY - .50f <= mEntities.back()->getY()) {
                randY += .50f;
        }

        // Do we need to spawn a Bonus Entity?
        if (CHANCE_BONUS >= Utils::Random::getInstance().random(0.f, 1.f)) {
                // Bonus will always be spawned on Static Platform
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
        // Dead weight, can normally not happen --> Create Static Platform
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
        // Dead weight, can normally not happen --> Create Spring
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
        // Otherwise error
        case Model::ePlayer:
                break;
        case Model::eBonus:
                break;
        case Model::eBackground:
                break;
        case Model::eScore:
                break;
        }
        // Entity needs to be initialized
        if (entity == nullptr) {
                return;
        }
        // If entity to be spawned is not a Bonus we can increase tha ActivePlatforms counter
        if (!entity->isBonus()) {
                mActivePlatforms++;
        }
        entity->setX(x);
        entity->setY(y);
        addEntity(entity);
}

bool World::checkDifficulty()
{
        // If current Difficulty is
        if (mDifficulty == Settings::Difficulty::eExtreme) {
                return false;
        }

        // Lambda function to check if new Difficulty can be set
        auto setDifficulty = [this](const float min, const float max, const float height,
                                    Settings::Difficulty diff) -> bool {
                if (height > min && height <= max && mDifficulty != diff) {
                        mDifficulty = diff;
                        return Settings::setDifficulty(diff);
                }
                return false;
        };

        // Change Difficulty according to current height
        const float height = Utils::Camera::getInstance().getMaxHeight();
        if (setDifficulty(0, 50.f, height, Settings::Difficulty::eEasy)) {
                return true;
        } else if (setDifficulty(50, 150.f, height, Settings::Difficulty::eNormal)) {
                return true;
        } else if (setDifficulty(150, 250.f, height, Settings::Difficulty::eDifficult)) {
                return true;
        } else if (setDifficulty(250, 350.f, height, Settings::Difficulty::eHard)) {
                return true;
        } else if (setDifficulty(350, 450.f, height, Settings::Difficulty::eInsane)) {
                return true;
        } else if (setDifficulty(450, 550.f, height, Settings::Difficulty::eExtreme)) {
                return true;
        }
        return false;
}

void World::removeEntities()
{
        // Traverse entities with iterator, otherwise we get a segmentation fault
        auto it = std::begin(mEntities);
        while (it != std::end(mEntities)) {
                // Check if Entity is removable
                if ((*it)->isRemovable()) {
                        // Decrease ActivePlatforms counter if we remove active Platform
                        // Clear still registered observers from subject (to make sure there aren't any mem leaks)
                        (*it)->onDestroy();
                        if (!(*it)->isBonus() && (*it)->getScore() != 0) {
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
        // Destroy Player
        mPlayer->onDestroy();
        // Destroy Entities
        for (const auto& i : mEntities) {
                i->onDestroy();
        }
        // Free Entities
        mEntities.clear();
        // Destroy Background tiles
        for (const auto& i : mBackground) {
                i->onDestroy();
        }
        // Free Background tiles
        mBackground.clear();
        // Destroy Score
        mScore->onDestroy();
        // Reset Camera
        Utils::Camera::getInstance().reset();
        // Reset Stopwatch
        Utils::Stopwatch::getInstance().reset();
}
