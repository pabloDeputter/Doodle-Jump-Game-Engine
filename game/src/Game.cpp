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
        p->setY(4.f);
        p->setY(14.4f);
        mWorld->addPlayer(a);

        //        mWorld->addEntity(mFactory->createPlatform());
        //        mWorld->addEntity(mFactory->createPlatform());

        while (mWindow->isOpen()) {

                Utils::Stopwatch::Delta();
                processEvents();
                mWorld->update();

                //                auto m = sf::Mouse::getPosition(*mWindow);
                //                std::cout << "mMouse: " << m.x << " : " << m.y << "\n";

                //                std::cout << "mPlayer: " << p->getX() << " : " << p->getY() << "\n";
                std::cout << "mPlayer: " << Utils::Camera::getInstance().transform(p->getX(), p->getY()).first << " : "
                          << Utils::Camera::getInstance().transform(0.f, p->getY()).second << "\n";

                //                auto &mCamera = Utils::Camera::getInstance();
                //                mCamera.move(p->getX(), p->getY());
                //                std::cout << "mCamera: " << mCamera.getPosition().first << " : " <<
                //                mCamera.getPosition().second << "\n";

                //                auto cc =
                //                Utils::Camera::getInstance().transform(Utils::Camera::getInstance().getPosition().first,
                //                                                                 Utils::Camera::getInstance().getPosition().second);
                //
                //
                //                std::cout << cc.first << " : " << cc.second << "\n";
                //
                //                mView.setCenter(cc.first, cc.second);

                //                mView.reset(sf::FloatRect(0.f, 0.f, (size_t) mWindow->getSize().x,
                //                                          (size_t) mWindow->getSize().y));
                //                mWindow->setView(mView);

                render();
        }
}