//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Game.h"

Game::Game()
{
        mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(800.f, 1440.f), "Doodle Jump");
        mFactory = std::make_shared<View::ConcreteFactory>(mWindow);
        mWorld = std::make_unique<World>(mFactory);
        mWindow->setFramerateLimit(60);

        // Set window dimensions
        Utils::Camera::getInstance().setWindowDimensions(800.f, 1440.f);

        // TODO - lol
        Utils::Resourcemanager::getInstance().addTexture(Model::ePlayer, "/Image/player.png");
        Utils::Resourcemanager::getInstance().addTexture(Model::eBackground, "/Image/background.png");
        Utils::Resourcemanager::getInstance().addTexture(Model::eStatic, "/Image/platformStatic.png");
        Utils::Resourcemanager::getInstance().addTexture(Model::eHorizontal, "/Image/platformHorizontal.png");
        Utils::Resourcemanager::getInstance().addTexture(Model::eVertical, "/Image/platformVertical.png");
        Utils::Resourcemanager::getInstance().addTexture(Model::eTemporary, "/Image/platformTemporary.png");
        Utils::Resourcemanager::getInstance().addTexture(Model::eSpring, "/Image/spring.png");
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
                // TODO - remove?
                case sf::Event::Resized:
                        Utils::Camera::getInstance().setWindowDimensions((float)mWindow->getSize().x,
                                                                         (float)mWindow->getSize().y);
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
        mWorld->initializeWorld();

        Utils::Stopwatch::getInstance().start();

        while (mWindow->isOpen()) {
                Utils::Stopwatch::getInstance().lap();
                processEvents();
                mWorld->update();
                render();
        }
}