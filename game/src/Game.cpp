//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Game.h"

Game::Game()
{
        mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(800.f, 1440.f), "Doodle Jump");
        mWorld = std::make_shared<World>();
        mFactory = std::make_shared<View::ConcreteFactory>(mWindow);
        mWindow->setFramerateLimit(60);

        Utils::Camera::getInstance().setWindowDimensions(800.f, 1440.f);
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
        mWindow->clear();
        mWorld->render();
        mWindow->display();
}

void Game::run()
{
        Utils::Stopwatch::Start();

        auto a = mFactory->createPlayer();
        auto p = a.first;
        mWorld->addPlayer(a);
        mWorld->addEntity(mFactory->createPlatform());
        mWorld->addEntity(mFactory->createPlatform());

        //        float lastY = 0.f;

        while (mWindow->isOpen()) {

                Utils::Stopwatch::Delta();
                processEvents();
                mWorld->update();

                auto x = Utils::Camera::getInstance().transform(p->getX(), p->getY());
                Utils::Camera::getInstance().move(x.first, x.second);

                //                mCamera.mCameraX = p->getX() - (float) mWindow->getSize().x / 2.f;
                //                mCamera.mCameraY = p->getY() - (float) mWindow->getSize().y / 2.f;

                //                if (mCamera.mCameraX < 0) mCamera.mCameraX = 0;
                //                if (mCamera.mCameraX > mWindow->getSize().x / 2.f) mCamera.mCameraX =
                //                mWindow->getSize().x / 2.f;

                auto mCamera = Utils::Camera::getInstance().getPosition();
                //                 TODO - if jumped platform, move up
                //                if (mCamera.second < lastY) lastY = mCamera.second;

                mView.reset(sf::FloatRect(0, 0, mWindow->getSize().x, mWindow->getSize().y));
                //                mView.reset(sf::FloatRect(mCamera.first, mCamera.second,(float) mWindow->getSize().x
                //                / 2.f, (float) mWindow->getSize().y / 2.f));
                mWindow->setView(mView);

                std::cout << mCamera.first << " : " << mCamera.second << "\n";

                //                mCamera.mCameraX = p->getX() - (float) mWindow->getSize().x / 2.f;
                //                mCamera.mCameraY = p->getY() - (float) mWindow->getSize().y / 2.f;

                //                if (mCamera.mCameraX < 0) mCamera.mCameraX = 0;
                //                if (mCamera.mCameraX > mWindow->getSize().x / 2.f) mCamera.mCameraX =
                //                mWindow->getSize().x / 2.f;

                //                mView.reset(sf::FloatRect(mCamera.mCameraX, mCamera.mCameraY, mWindow->getSize().x,
                //                mWindow->getSize().y)); mView.reset(sf::FloatRect(mCamera.mCameraX,
                //                mCamera.mCameraY,(float) mWindow->getSize().x / 2.f, (float) mWindow->getSize().y
                //                / 2.f)); mWindow->setView(mView);

                render();
        }
}