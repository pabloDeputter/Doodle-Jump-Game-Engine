//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Game.h"
#include "EnterScoreState.h"
#include "GameState.h"
#include "MenuState.h"

Game::Game(unsigned int width, unsigned int height)
{
        mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "Doodle Jump", sf::Style::Close);
        mFactory = std::make_shared<Factory::ConcreteFactory>(mWindow);
        //        mWindow->setFramerateLimit(60);
        mWindow->setVerticalSyncEnabled(true);

        Game::initializeResources();

        Utils::Camera::getInstance().setWindowDimensions((float)width, (float)height);

        mStateType = eGame;
        mState = std::make_shared<GameState>(std::make_unique<World>(mFactory, true), mWindow, *this);
}

void Game::initializeResources()
{
        try {
                // Textures
                Utils::Resourcemanager::getInstance().addTexture(Model::ePlayer, "/image/player.png");
                Utils::Resourcemanager::getInstance().addTexture(Model::eBackground, "/image/background.png");
                Utils::Resourcemanager::getInstance().addTexture(Model::eStatic, "/image/platformStatic.png");
                Utils::Resourcemanager::getInstance().addTexture(Model::eHorizontal, "/image/platformHorizontal.png");
                Utils::Resourcemanager::getInstance().addTexture(Model::eVertical, "/image/platformVertical.png");
                Utils::Resourcemanager::getInstance().addTexture(Model::eTemporary, "/image/platformTemporary.png");
                Utils::Resourcemanager::getInstance().addTexture(Model::eSpring, "/image/spring.png");
                Utils::Resourcemanager::getInstance().addTexture(Model::eJetpack, "/image/jetpack.png");

                // Fonts
                Utils::Resourcemanager::getInstance().addFont(Model::eScore, "/font/score.ttf");

                // Sounds
                Utils::Resourcemanager::getInstance().addSound(Model::eStatic, "/audio/cartoon-jump-6462.wav");

        } catch (const std::exception& exc) {
                std::cerr << exc.what();
        }
}

void Game::run()
{
        Utils::Stopwatch::getInstance().start();
        while (mWindow->isOpen()) {
                if (mState->getType() != mStateType) {
                        switch (mStateType) {
                        case eGame:
                                mState = std::make_shared<GameState>(std::make_unique<World>(mFactory, true), mWindow,
                                                                     *this);
                                break;
                        case eEnterScore:
                                // highscore - buffer
                                mState = std::make_shared<EnterScoreState>(mWindow, *this);
                                break;
                        case eMenu:
                                mState = std::make_shared<MenuState>(mWindow, *this);
                                break;
                        }
                }

                Utils::Stopwatch::getInstance().lap();
                mState->processEvents();
                mState->update();
                mState->render();
        }
}