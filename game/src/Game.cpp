//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Game.h"

Game::Game(unsigned int width, unsigned int height)
{
        mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "Doodle Jump", sf::Style::Close);
        mFactory = std::make_shared<View::ConcreteFactory>(mWindow);
        mWorld = std::make_unique<World>(mFactory);
        //        mWindow->setFramerateLimit(60);
        mWindow->setVerticalSyncEnabled(true);

        // Set window dimensions
        Utils::Camera::getInstance().setWindowDimensions((float)width, (float)height);

        // Set path of different textures
        Game::initializeResources();
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

void Game::processEvents()
{
        sf::Event event;
        while (mWindow->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::KeyPressed:
                        Game::handlePlayerInput(event.key.code, true);
                        break;
                case sf::Event::KeyReleased:
                        Game::handlePlayerInput(event.key.code, false);
                        break;
                case sf::Event::Closed:
                        mWindow->close();
                        break;
                }
        }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
        if (key == sf::Keyboard::Z) {
                mWorld->events("Z", isPressed);
        } else if (key == sf::Keyboard::S) {
                mWorld->events("S", isPressed);
        } else if (key == sf::Keyboard::Q) {
                mWorld->events("Q", isPressed);
        } else if (key == sf::Keyboard::D) {
                mWorld->events("D", isPressed);
        }
}

void Game::render()
{
        mWindow->clear(sf::Color(20, 20, 35));
        mWorld->render();
        mWindow->display();
}

void Game::run()
{
        mWorld->initWorld();
        Utils::Stopwatch::getInstance().start();

        while (mWindow->isOpen()) {
                Utils::Stopwatch::getInstance().lap();
                processEvents();
                mWorld->update();
                render();
        }
}
