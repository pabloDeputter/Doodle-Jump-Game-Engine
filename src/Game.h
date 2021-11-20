//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H

#include "Controllers/IController.h"
#include "Controllers/PlayerController.h"
#include "Views/IView.h"
#include "Views/PlayerView.h"

#include "Utils/Stopwatch.h"
#include "Utils/Transform.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>

class Game
{
        std::shared_ptr<sf::RenderWindow> mWindow;
        std::unique_ptr<Controller::IController> mPlayerController;

        std::shared_ptr<View::IView> v;
        std::shared_ptr<Model::Entity> p;

        sf::Sprite mPlayer;
        sf::RectangleShape mCollisionBox;
        sf::Texture mTexture;
        sf::IntRect mRect;
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
        Game();

        void processEvents();

        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

        void render();

        void run();

        void autoJump(float deltaTime)
        {

                if (mIsMovingDown && mIsMovingUp) {
                        mIsMovingDown = false;
                        mIsMovingUp = false;
                }

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
                }

                mCollisionBox.move(currentVelocity.x * deltaTime * 56.657223796033994f,
                                   currentVelocity.y * deltaTime * 56.657223796033994f);

                mPlayer.move(currentVelocity.x * deltaTime * 56.657223796033994f,
                             currentVelocity.y * deltaTime * 56.657223796033994f);

                //                std::cout << "DT: " << deltaTime << " - "
                //                          << "FPS: " << 1.f / deltaTime << std::endl;
        }
};

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_GAME_H
