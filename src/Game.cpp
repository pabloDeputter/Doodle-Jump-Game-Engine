//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Game.h"

Game::Game()
{

        mWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(1000, 2060), "Doodle Jump");
        //        mWindow->setFramerateLimit(60);
        mPlayer.setSize(sf::Vector2f(50.f, 50.f));
        mPlayer.setFillColor(sf::Color::Cyan);
        mPlayer.setPosition(500.f, 500.f);

        mCollisionBox.setOutlineColor(sf::Color::Red);
        mCollisionBox.setOutlineThickness(1.f);
        mCollisionBox.setFillColor(sf::Color::Transparent);
        mCollisionBox.setSize(sf::Vector2f(50.f, 50.f));
        mCollisionBox.scale(1.4f, 1.4f);

        Utils::Transform::SetDimensions((float)mWindow->getSize().x, (float)mWindow->getSize().y);
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
                mIsMovingUp = isPressed;
        } else if (key == sf::Keyboard::S) {
                mIsMovingDown = isPressed;
        } else if (key == sf::Keyboard::Q) {
                mIsMovingLeft = isPressed;
        } else if (key == sf::Keyboard::D) {
                mIsMovingRight = isPressed;
        }
}

void Game::render()
{
        mWindow->clear();
        mCollisionBox.setPosition(mPlayer.getPosition().x - 0.2f * mPlayer.getSize().x,
                                  mPlayer.getPosition().y - 0.2f * mPlayer.getSize().y);
        mWindow->draw(mCollisionBox);
        mWindow->draw(mPlayer);
        mWindow->display();
}

void Game::run()
{
        Utils::Stopwatch::Start();

        while (mWindow->isOpen()) {
                processEvents();
                update(Utils::Stopwatch::Delta());
                //                autoJump(Utils::Stopwatch::Delta());
                render();
        }
}