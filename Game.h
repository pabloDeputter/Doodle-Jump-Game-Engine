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
        sf::Sprite mPlayer;
        sf::Texture mTexture;
        bool mIsMovingUp;
        bool mIsMovingDown;
        bool mIsMovingLeft;
        bool mIsMovingRight;

        sf::Vector2f currentVelocity;
        sf::Vector2f currentDirection;
        float maxVelocity = 50.f;
        float acceleration = 2.f;
        float drag = .5f;

public:
        Game() : mWindow(sf::VideoMode(3840, 2060), "Doodle Jump"), mPlayer()
        {
                if (!mTexture.loadFromFile("texture_1.png")) {
                        std::cerr << "error loading tex\n";
                }
                mPlayer.setTexture(mTexture);
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
        void update(sf::Time deltaTime)
        {
                currentDirection = sf::Vector2f(0.f, 0.f);

                sf::Vector2f movement(0.f, 0.f);
                if (mIsMovingUp) {
                        currentDirection.y -= 1.f;

                        if (currentVelocity.y < maxVelocity) {
                                currentVelocity.y += acceleration * currentDirection.y;
                        }
                        //                        movement.y -= 1.f;
                }
                if (mIsMovingDown) {
                        currentDirection.y += 1.f;

                        if (currentVelocity.y > -maxVelocity) {
                                currentVelocity.y += acceleration * currentDirection.y;
                        }
                        //                        movement.y += 1.f;
                }
                if (mIsMovingLeft) {
                        currentDirection.x -= 1.f;

                        if (currentVelocity.x > -maxVelocity) {
                                currentVelocity.x += acceleration * currentDirection.x;
                        }

                        //                        movement.x -= 1.f;
                }
                if (mIsMovingRight) {
                        currentDirection.x += 1.f;

                        if (currentVelocity.x < maxVelocity) {
                                currentVelocity.x += acceleration * currentDirection.x;
                        }
                        //                        movement.x += 1.f;
                }
                // Drag
                if (currentVelocity.x > 0.f) {

                        currentVelocity.x -= drag;
                        if (currentVelocity.x < 0.f) {
                                // Velocity can't be negative, just slow down
                                currentVelocity.x = 0.0f;
                        }
                } else if (currentVelocity.y < 0.f) {

                        currentVelocity.y += drag;
                        if (currentVelocity.y > 0.f) {
                                // Velocity can't be negative, just slow down
                                currentVelocity.y = 0.0f;
                        }
                }
                if (currentVelocity.y > 0.f) {

                        currentVelocity.y -= drag;
                        if (currentVelocity.y < 0.f) {
                                // Velocity can't be negative, just slow down
                                currentVelocity.y = 0.0f;
                        }
                } else if (currentVelocity.x < 0.f) {

                        currentVelocity.x += drag;
                        if (currentVelocity.x > 0.f) {
                                // Velocity can't be negative, just slow down
                                currentVelocity.x = 0.0f;
                        }
                }

                // Finally move
                mPlayer.move(currentVelocity.x, currentVelocity.y);

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
                Utils::Stopwatch::Start();
                float timeSinceLastUpdate = 0.0f;
                float frameRate = 60.0f;
                // Time per frame in milliseconds
                float timePerFrame = (1000.0f / frameRate);

                while (mWindow.isOpen()) {
                        processEvents();
                        auto a = Utils::Stopwatch::Delta();
                        timeSinceLastUpdate += a;

                        //                        if (timeSinceLastUpdate < timePerFrame) {
                        //                                auto ms_sleep = timePerFrame - timeSinceLastUpdate;
                        //                                std::chrono::milliseconds ms{static_cast<long int>(ms_sleep)};
                        //                                std::this_thread::sleep_for(std::chrono::milliseconds(ms));
                        //                        }
                        //                        processEvents();
                        //                        update(sf::milliseconds(1000.0f / 60.0f));
                        //
                        while (timeSinceLastUpdate > timePerFrame) {
                                timeSinceLastUpdate -= timePerFrame;
                                processEvents();
                                update(sf::milliseconds((int32_t)timePerFrame));
                                //                                update(sf::milliseconds(1.0f / 60.0f));
                        }
                        render();
                }
        }
};
} // namespace Game

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
