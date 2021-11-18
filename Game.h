//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "src/Utils/Stopwatch.h"
#include <iostream>
#include <thread>

namespace Game {

class Game
{
        sf::RenderWindow mWindow;
        //        sf::Sprite mPlayer;
        sf::Sprite mPlayer;
        sf::Texture mTexture;
        bool mIsMovingUp;
        bool mIsMovingDown;
        bool mIsMovingLeft;
        bool mIsMovingRight;

        sf::Vector2f currentVelocity;
        sf::Vector2f currentDirection;
        float maxVelocity = 27.f;
        float acceleration = 1.5f;
        float drag = 0.6f;

public:
        Game() : mWindow(sf::VideoMode(3840, 2060), "Doodle Jump"), mPlayer()
        {
                //                mWindow.setFramerateLimit(60);
                if (!mTexture.loadFromFile("texture_2.png")) {
                        std::cerr << "error loading tex\n";
                }
                //                mPlayer.setSize({100.f, 100.f});
                //                mPlayer.setFillColor(sf::Color::Cyan);
                mPlayer.setPosition(2048.f, 100.f);
                mPlayer.setTexture(mTexture);
                mPlayer.setScale(1.f, 1.f);
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

        void autoJump(float deltaTime)
        {

                if (mIsMovingDown && mIsMovingUp) {
                        mIsMovingDown = false;
                        mIsMovingUp = false;
                }

                //                std::cout << "Current velocity.y: " << currentVelocity.y << std::endl;
                currentDirection = sf::Vector2f(0.f, 0.f);

                // Collision with bounce
                if (mPlayer.getPosition().y >= 1000 && !mIsMovingDown &&
                    mPlayer.getPosition().y + (float)(currentVelocity.y * deltaTime * 56.657223796033994f) >= 1000) {

                        //                        mIsMovingLeft = false; mIsMovingRight = false;

                        currentVelocity *= -1.f;
                        mPlayer.move(currentVelocity.x * deltaTime * 56.657223796033994f,
                                     currentVelocity.y * deltaTime * 56.657223796033994f);
                }

                if (mIsMovingLeft) {
                        currentDirection.x = -1.f;

                        if (currentVelocity.x > -maxVelocity) {
                                currentVelocity.x +=
                                    acceleration * currentDirection.x * deltaTime * 56.657223796033994f;
                        }
                } else if (mIsMovingRight) {
                        currentDirection.x = 1.f;

                        if (currentVelocity.x < maxVelocity) {
                                currentVelocity.x +=
                                    acceleration * currentDirection.x * deltaTime * 56.657223796033994f;
                        }
                }

                //                 Move up / down
                if (currentVelocity.y >= 0) {
                        //                        std::cout << "Falling...\n";
                        currentDirection.y = 1.f;
                        if (currentVelocity.y < maxVelocity) {
                                currentVelocity.y +=
                                    acceleration * currentDirection.y * deltaTime * 56.657223796033994f;
                        }
                }
                //                else if (currentVelocity.y < 0) {
                //                        std::cout << "Jumping...\n";
                //                        currentDirection.y = -1.f;
                //                        if (currentVelocity.y > -maxVelocity) {
                //                                currentVelocity.y +=
                //                                    acceleration * currentDirection.y * deltaTime
                //                                    * 56.657223796033994f;
                //                        }
                //                }

                // Drag
                if (currentVelocity.y > 0.f) {
                        currentVelocity.y -= drag * deltaTime * 56.657223796033994f;
                        if (currentVelocity.y < 0.f) {
                                // Velocity can't be negative, just slow down
                                currentVelocity.y = 0.0f;
                        }
                } else if (currentVelocity.y < 0.f) {
                        currentVelocity.y += drag * deltaTime * 56.657223796033994f;
                        if (currentVelocity.y > 0.f) {
                                // Velocity can't be negative, just slow down
                                currentVelocity.y = 0.0f;
                        }
                }
                if (currentVelocity.x > 0.f) {

                        currentVelocity.x -= drag * deltaTime * 56.657223796033994f;
                        if (currentVelocity.x < 0.f) {
                                // Velocity can't be negative, just slow down
                                currentVelocity.x = 0.0f;
                        }
                } else if (currentVelocity.x < 0.f) {

                        currentVelocity.x += drag * deltaTime * 56.657223796033994f;
                        if (currentVelocity.x > 0.f) {
                                // Velocity can't be negative, just slow down
                                currentVelocity.x = 0.0f;
                        }
                }

                mPlayer.move(currentVelocity.x * deltaTime * 56.657223796033994f,
                             currentVelocity.y * deltaTime * 56.657223796033994f);
        }

        void update(float deltaTime)
        {

                currentDirection = sf::Vector2f(0.f, 0.f);

                sf::Vector2f movement(0.f, 0.f);
                // Movement + Direction
                if (mIsMovingUp) {
                        currentDirection.y = -1.f;

                        if (currentVelocity.y > -maxVelocity) {
                                currentVelocity.y +=
                                    acceleration * currentDirection.y * deltaTime * 56.657223796033994f;
                        }
                } else if (mIsMovingDown) {

                        if (mPlayer.getPosition().y >= 1000)
                                return;

                        currentDirection.y = 1.f;

                        if (currentVelocity.y < maxVelocity) {
                                currentVelocity.y +=
                                    acceleration * currentDirection.y * deltaTime * 56.657223796033994f;
                        }

                } else if (mIsMovingLeft) {
                        currentDirection.x = -1.f;

                        if (currentVelocity.x > -maxVelocity) {
                                currentVelocity.x +=
                                    acceleration * currentDirection.x * deltaTime * 56.657223796033994f;
                        }
                } else if (mIsMovingRight) {
                        currentDirection.x = 1.f;

                        if (currentVelocity.x < maxVelocity) {
                                currentVelocity.x +=
                                    acceleration * currentDirection.x * deltaTime * 56.657223796033994f;
                        }
                }

                // Drag
                if (currentVelocity.x > 0.f) {

                        currentVelocity.x -= drag * deltaTime * 56.657223796033994f;
                        if (currentVelocity.x < 0.f) {
                                // Velocity can't be negative, just slow down
                                currentVelocity.x = 0.0f;
                        }
                } else if (currentVelocity.x < 0.f) {

                        currentVelocity.x += drag * deltaTime * 56.657223796033994f;
                        if (currentVelocity.x > 0.f) {
                                // Velocity can't be negative, just slow down
                                currentVelocity.x = 0.0f;
                        }
                }
                if (currentVelocity.y > 0.f) {
                        currentVelocity.y -= drag * deltaTime * 56.657223796033994f;
                        if (currentVelocity.y < 0.f) {
                                // Velocity can't be negative, just slow down
                                currentVelocity.y = 0.0f;
                        }
                } else if (currentVelocity.y < 0.f) {
                        currentVelocity.y += drag * deltaTime * 56.657223796033994f;
                        if (currentVelocity.y > 0.f) {
                                // Velocity can't be negative, just slow down
                                currentVelocity.y = 0.0f;
                        }
                }

                // Collision with bounce
                if (mPlayer.getPosition().y >= 1000 && !mIsMovingDown &&
                    mPlayer.getPosition().y + (float)(currentVelocity.y * deltaTime * 56.657223796033994f) >= 1000) {
                        currentVelocity *= -1.f;
                        mPlayer.move(currentVelocity.x * deltaTime * 56.657223796033994f,
                                     currentVelocity.y * deltaTime * 56.657223796033994f);
                } else {
                        mPlayer.move(currentVelocity.x * deltaTime * 56.657223796033994f,
                                     currentVelocity.y * deltaTime * 56.657223796033994f);
                }

                std::cout << "DT: " << deltaTime << " - "
                          << "FPS: " << 1.f / deltaTime << std::endl;
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

                while (mWindow.isOpen()) {
                        processEvents();
                        //                        update(Utils::Stopwatch::Delta());
                        autoJump(Utils::Stopwatch::Delta());

                        render();
                }
        }
};
} // namespace Game

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
