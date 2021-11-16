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
        sf::RectangleShape mPlayer;
        sf::Texture mTexture;
        bool mIsMovingUp;
        bool mIsMovingDown;
        bool mIsMovingLeft;
        bool mIsMovingRight;

        sf::Vector2f currentVelocity;
        sf::Vector2f currentDirection;
        float maxVelocity = 25.f;
        float acceleration = 2.5f;
        float drag = 0.5f;

public:
        Game() : mWindow(sf::VideoMode(3840, 2060), "Doodle Jump"), mPlayer()
        {
                mWindow.setFramerateLimit(60);
                if (!mTexture.loadFromFile("texture_1.png")) {
                        std::cerr << "error loading tex\n";
                }
                mPlayer.setSize({100.f, 100.f});
                mPlayer.setFillColor(sf::Color::Cyan);
                mPlayer.setPosition(200.f, 100.f);
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
        void update(float deltaTime)
        {
                std::cout << "DeltaTime: " << deltaTime << std::endl;
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

                // Finally move
                mPlayer.move(currentVelocity.x * deltaTime * 56.657223796033994f,
                             currentVelocity.y * deltaTime * 56.657223796033994f);

                //                movement.x = movement.x * (float)deltaTime.asMilliseconds();
                //                movement.y = movement.y * (float)deltaTime.asMilliseconds();
                //                mPlayer.move(movement);
        }
        void render()
        {
                mWindow.clear();
                mWindow.draw(mPlayer);
                mWindow.display();
        }
        void run()
        {
                sf::Clock clock;
                float dt;

                Utils::Stopwatch::Start();
                //                float timeSinceLastUpdate = 0.f;
                //                float frameRate = 60.f;
                ////                 Time per frame in milliseconds
                //                float timePerFrame = (1000.f / frameRate);

                while (mWindow.isOpen()) {
                        processEvents();

                        dt = clock.restart().asSeconds();
                        std::cout << "sf::Clock: " << dt << std::endl;
                        //                        std::cout << "Utils::Stopwatch: " << Utils::Stopwatch::Delta() <<
                        //                        std::endl;
                        update(Utils::Stopwatch::Delta());

                        //                        timeSinceLastUpdate += Utils::Stopwatch::Delta();
                        //                        while (timeSinceLastUpdate > timePerFrame) {
                        //                                timeSinceLastUpdate -= timePerFrame;
                        //                                processEvents();
                        //                                update(timeSinceLastUpdate);
                        //                        }
                        render();
                }
        }
};
} // namespace Game

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
