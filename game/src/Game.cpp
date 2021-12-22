//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Game.h"

#include "state/MenuState.h"

Game::Game(unsigned int width, unsigned int height)
{
        // Create window
        mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "Doodle Jump", sf::Style::Close);
        Utils::Camera::getInstance().setWindowDimensions((float)width, (float)height);
        // Initialize AbstractFactory with ConcreteFactory
        mFactory = std::make_shared<Factory::ConcreteFactory>(mWindow);
        //        mWindow->setFramerateLimit(20);
        mWindow->setVerticalSyncEnabled(true);
        // Initialize resources
        Game::initializeResources();
        // Enter game State
        mStates.push(std::make_shared<States::MenuState>(mWindow, *this));
}

void Game::initializeResources()
{
        // Try loading resources
        try {
                // Textures - entities
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eBackground, "/image/background_1.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::ePlayer, "/image/character_1.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eStatic, "/image/platformStatic.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eHorizontal,
                                                                 "/image/platformHorizontal.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eVertical, "/image/platformVertical.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eTemporary,
                                                                 "/image/platformTemporary.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eSpring, "/image/spring.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eJetpack, "/image/jetpack.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eCoin, "/image/coin.png");
                // Fonts - entities
                Utils::ResourceManager::getInstance().addFont(Utils::Type::eScore, "/font/super_mario_bros.ttf");

                // Textures - menu
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eMenuLogo, "/image/doodleJump.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eMenuItemBack, "/image/rectangle.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eShopCh1, "/image/character_1.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eShopCh2, "/image/character_2.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eShopCh3, "/image/character_3.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eShopBg1, "/image/background_1.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eShopBg2, "/image/background_2.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eShopBg3, "/image/background_3.png");

                // Fonts - menu
                Utils::ResourceManager::getInstance().addFont(Utils::Type::eMenuHighScores,
                                                              "/font/super_mario_bros.ttf");
                Utils::ResourceManager::getInstance().addFont(Utils::Type::eMenuInfo, "/font/alagard.ttf");
                // Sound - menu
                Utils::ResourceManager::getInstance().addSound(Utils::Type::eMenuInfo, "/audio/theme.wav");

        } catch (const std::exception& exc) {
                std::cerr << exc.what();
        }
}

void Game::run()
{
        // Start stopwatch
        Utils::Stopwatch::getInstance().start();
        // Main game loop
        while (mWindow->isOpen()) {
                Utils::Stopwatch::getInstance().lap();
                // Process events
                mStates.top()->processEvents();
                // Update
                mStates.top()->update();
                // Render to screen
                mStates.top()->render();
        }
}