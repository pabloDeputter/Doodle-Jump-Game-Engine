//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Game.h"

Game::Game()
{

        mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 2060), "Doodle Jump");
        mWorld = std::make_shared<World>();
        mFactory = std::make_shared<View::ConcreteFactory>(mWindow);
        mWindow->setFramerateLimit(60);
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
        mWindow->clear();
        mWorld->render();
        mWindow->display();
}

void Game::run()
{
        Utils::Stopwatch::Start();

        mWorld->addPlayer(mFactory->createPlayer());
        mWorld->addEntity(mFactory->createPlatform());
        //        mWorld->addEntity(mFactory->createPlatform());

        while (mWindow->isOpen()) {

                Utils::Stopwatch::Delta();
                processEvents();
                mWorld->update();
                render();
        }
}