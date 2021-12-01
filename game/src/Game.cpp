//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Game.h"

Game::Game()
{
        mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(800.f, 1440.f), "Doodle Jump");
        mFactory = std::make_shared<View::ConcreteFactory>(mWindow);
        mWorld = std::make_shared<World>(mFactory);
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
        mWindow->clear(sf::Color(20, 20, 35));
        mWorld->render();
        mWindow->display();
}

void Game::run()
{
        mWorld->initializeWorld();

        Utils::Stopwatch::Start();

        auto a = mFactory->createPlayer();
        auto p = a.first;
        auto b = mFactory->createStaticPlatform();
        b.first->setX(Utils::Camera::getInstance().getGameDimensiosn().first / 2.f);
        b.first->setY((Utils::Camera::getInstance().getGameDimensiosn().second / 2.f) + 1.f);

        mWorld->addEntity(b);
        mWorld->addPlayer(a);
        mWorld->addEntity(mFactory->createPlatform());
        mWorld->addEntity(mFactory->createPlatform());

        float mMaxHeight = 0.f;

        //        float lastY = 0.f;

        while (mWindow->isOpen()) {

                Utils::Stopwatch::Delta();
                processEvents();
                mWorld->update();

                std::cout << p->getX() << " : " << p->getY() << "\n";
                if (p->getY() < mMaxHeight) {
                        mMaxHeight = p->getY();
                }

                //                std::cout << "p: " << p->getX() << " : " << p->getY() << "\n";
                //                // Transform player world coordinates --> screen coordinates
                //                auto x = Utils::Camera::getInstance().transform(p->getX(), p->getY());
                //                std::cout << "x: " << x.first << " : " << x.second << "\n";
                //
                //                // Move camera with screen coordinates of player
                //                Utils::Camera::getInstance().move(x.first, x.second);
                //                std::cout << "mCamera: " << Utils::Camera::getInstance().getPosition().second << "\n";

                //                auto x_ = Utils::Camera::getInstance().transform(0.f, -mMaxHeight);
                //                Utils::Camera::getInstance().move(0.f, mMaxHeight);

                //                if (mCamera.mCameraX < 0) mCamera.mCameraX = 0;
                //                if (mCamera.mCameraX > mWindow->getSize().x / 2.f) mCamera.mCameraX =
                //                mWindow->getSize().x / 2.f;

                //                 TODO - if jumped platform, move up
                //                if (mCamera.second < lastY) lastY = mCamera.second;

                mView.reset(sf::FloatRect(0.f, Utils::Camera::getInstance().getPosition().second, mWindow->getSize().x,
                                          mWindow->getSize().y));
                //                                mView.reset(sf::FloatRect(mCamera.first, mCamera.second,(float)
                //                                mWindow->getSize().x
                //                / 2.f, (float) mWindow->getSize().y / 2.f));
                mWindow->setView(mView);

                //                std::cout << mCamera.first << " : " << mCamera.second << "\n";

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