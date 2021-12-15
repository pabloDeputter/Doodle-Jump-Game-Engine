//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Game.h"

#include "state/EnterScoreState.h"
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
        mStateType = ePlay;
        mState = std::make_shared<States::PlayState>(std::make_unique<World>(mFactory, true), mWindow, *this);
}

void Game::initializeResources()
{
        // Try loading resources
        try {
                // Textures
                Utils::ResourceManager::getInstance().addTexture(Model::ePlayer, "/image/player.png");
                Utils::ResourceManager::getInstance().addTexture(Model::eBackground, "/image/background.png");
                Utils::ResourceManager::getInstance().addTexture(Model::eStatic, "/image/platformStatic.png");
                Utils::ResourceManager::getInstance().addTexture(Model::eHorizontal, "/image/platformHorizontal.png");
                Utils::ResourceManager::getInstance().addTexture(Model::eVertical, "/image/platformVertical.png");
                Utils::ResourceManager::getInstance().addTexture(Model::eTemporary, "/image/platformTemporary.png");
                Utils::ResourceManager::getInstance().addTexture(Model::eSpring, "/image/spring.png");
                Utils::ResourceManager::getInstance().addTexture(Model::eJetpack, "/image/jetpack.png");

                // Fonts
                Utils::ResourceManager::getInstance().addFont(Model::eScore, "/font/score.ttf");

                // Sounds
                Utils::ResourceManager::getInstance().addSound(Model::eStatic, "/audio/cartoon-jump-6462.wav");

        } catch (const std::exception& exc) {
                std::cerr << exc.what();
        }
}

void Game::checkState()
{
        if (mState->getType() != mStateType) {
                switch (mStateType) {
                case ePlay:
                        mState = std::make_shared<States::PlayState>(std::make_unique<World>(mFactory, true), mWindow,
                                                                     *this);
                        break;
                case eEnterScore:
                        // highscore - buffer
                        mState = std::make_shared<States::EnterScoreState>(mWindow, *this);
                        break;
                case eMenu:
                        mState = std::make_shared<States::MenuState>(mWindow, *this);
                        break;
                }
        }
}

void Game::run()
{
        // Start stopwatch
        Utils::Stopwatch::getInstance().start();
        // Main game loop
        while (mWindow->isOpen()) {
                checkState();
                [[maybe_unused]] float lap = Utils::Stopwatch::getInstance().lap();
                // Process events
                mState->processEvents();
                checkState();
                // Update
                mState->update();
                checkState();
                // Render to screen
                mState->render();
        }
}