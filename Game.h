//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "src/Utils/Stopwatch.h"
#include <iostream>

namespace Game {

class Game
{
        sf::RenderWindow mWindow;
        sf::CircleShape mPlayer;
        bool mIsMovingUp;
        bool mIsMovingDown;
        bool mIsMovingLeft;
        bool mIsMovingRight;

public:
        Game() : mWindow(sf::VideoMode(750, 1000), "Doodle Jump"), mPlayer()
        {
                mPlayer.setRadius(40.f);
                mPlayer.setPosition(100.f, 100.f);
                mPlayer.setFillColor(sf::Color::Cyan);
        }

        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
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

        void processEvents()
        {
                sf::Event event;
                while (mWindow.pollEvent(event)) {

                        switch (event.type) {
                        case sf::Event::KeyPressed:
                                handlePlayerInput(event.key.code, true);
                                break;
                        case sf::Event::KeyReleased:
                                handlePlayerInput(event.key.code, false);
                                break;
                        case sf::Event::Closed:
                                mWindow.close();
                                break;
                        }
                }
        }
        void update(sf::Time deltaTime)
        {
                sf::Vector2f movement(0.f, 0.f);
                if (mIsMovingUp)
                        movement.y -= 1.f;
                if (mIsMovingDown)
                        movement.y += 1.f;
                if (mIsMovingLeft)
                        movement.x -= 1.f;
                if (mIsMovingRight)
                        movement.x += 1.f;
                mPlayer.move(movement * deltaTime.asSeconds());
        }
        void render()
        {
                mWindow.clear();
                mWindow.draw(mPlayer);
                mWindow.display();
        }
        void run()
        {
                Utils::Stopwatch::Start();
                float timeSinceLastUpdate = 0.0f;
                float timePerFrame = (1.0 / 60.0f);

                //                sf::Clock clock;
                //                sf::Time timeSinceLastUpdate = sf::Time::Zero;
                //                auto timePerFrame = sf::seconds(1.0f / 60.0f);

                while (mWindow.isOpen()) {
                        processEvents();
                        timeSinceLastUpdate += Utils::Stopwatch::Delta();
                        //                        timeSinceLastUpdate += clock.restart();
                        while (timeSinceLastUpdate > timePerFrame) {
                                timeSinceLastUpdate -= timePerFrame;
                                processEvents();
                                update(sf::seconds(1.0 / 60.0f));
                        }
                        render();
                }
        }
};
} // namespace Game

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
