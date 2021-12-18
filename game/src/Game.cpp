//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Game.h"

#include "state/MenuState.h"
#include "state/PlayState.h"

Game::Game(unsigned int width, unsigned int height)
{
        // Create window
        mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "Doodle Jump", sf::Style::Close);
        Utils::Camera::getInstance().setWindowDimensions((float)width, (float)height);
        // Initialize AbstractFactory with ConcreteFactory
        mFactory = std::make_shared<Factory::ConcreteFactory>(mWindow);
        //        mWindow->setFramerateLimit(60);
        mWindow->setVerticalSyncEnabled(true);
        // Initialize resources
        Game::initializeResources();
        // Enter game State
        mStateType = eMenu;
        mState = std::make_shared<States::MenuState>(mWindow, *this);
        mStates.push(std::make_shared<States::MenuState>(mWindow, *this));
}

void Game::initializeResources()
{
        // Try loading resources
        try {
                // Textures - entities
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eBackground, "/image/background.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::ePlayer, "/image/player.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eStatic, "/image/platformStatic.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eHorizontal,
                                                                 "/image/platformHorizontal.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eVertical, "/image/platformVertical.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eTemporary,
                                                                 "/image/platformTemporary.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eSpring, "/image/spring.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eJetpack, "/image/jetpack.png");
                // Fonts - entities
                Utils::ResourceManager::getInstance().addFont(Utils::Type::eScore, "/font/super_mario_bros.ttf");
                // Sounds - entities
                Utils::ResourceManager::getInstance().addSound(Utils::Type::eStatic, "/audio/cartoon-jump-6462.wav");

                // Textures - menu
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eMenuLogo, "/image/doodleJump.png");
                Utils::ResourceManager::getInstance().addTexture(Utils::Type::eMenuCursor, "/image/cursor.png");
                // Fonts - menu
                Utils::ResourceManager::getInstance().addFont(Utils::Type::eMenuHighScores,
                                                              "/font/super_mario_bros.ttf");
                Utils::ResourceManager::getInstance().addFont(Utils::Type::eMenuInfo, "/font/alagard.ttf");
                Utils::ResourceManager::getInstance().addFont(Utils::Type::eMenuSettings, "/font/alagard.ttf");

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