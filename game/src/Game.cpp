//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Game.h"

Game::Game(unsigned int width, unsigned int height)
{
        mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "Doodle Jump", sf::Style::Close);
        mFactory = std::make_shared<View::ConcreteFactory>(mWindow);
        mWorld = std::make_unique<World>(mFactory);
        //        mWindow->setFramerateLimit(60);
        mWindow->setVerticalSyncEnabled(true);

        // Set window dimensions
        Utils::Camera::getInstance().setWindowDimensions((float)width, (float)height);

        // Set path of different textures
        Game::initializeResources();
}

void Game::initializeResources()
{
        try {
                // Textures
                Utils::Resourcemanager::getInstance().addTexture(Model::ePlayer, "/image/player.png");
                Utils::Resourcemanager::getInstance().addTexture(Model::eBackground, "/image/background.png");
                Utils::Resourcemanager::getInstance().addTexture(Model::eStatic, "/image/platformStatic.png");
                Utils::Resourcemanager::getInstance().addTexture(Model::eHorizontal, "/image/platformHorizontal.png");
                Utils::Resourcemanager::getInstance().addTexture(Model::eVertical, "/image/platformVertical.png");
                Utils::Resourcemanager::getInstance().addTexture(Model::eTemporary, "/image/platformTemporary.png");
                Utils::Resourcemanager::getInstance().addTexture(Model::eSpring, "/image/spring.png");
                Utils::Resourcemanager::getInstance().addTexture(Model::eJetpack, "/image/jetpack.png");

                // Fonts
                Utils::Resourcemanager::getInstance().addFont(Model::eScore, "/font/score.ttf");

                // Sounds
                Utils::Resourcemanager::getInstance().addSound(Model::eStatic, "/audio/cartoon-jump-6462.wav");

        } catch (const std::exception& exc) {
                std::cerr << exc.what();
        }
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
        mWindow->clear(sf::Color(20, 20, 35));
        mWorld->render();
        mWindow->display();
}

void Game::drawHighScoreTable()
{
        // TODO - doen met view????
        // todo - event

        static std::unique_ptr<sf::Text> high;
        if (high == nullptr) {
                std::cout << "lol\n";
                high = std::make_unique<sf::Text>();
                high->setLineSpacing(2.f);
                high->setFillColor(sf::Color::Black);
                high->setFont(*Utils::Resourcemanager::getInstance().getFonts()->get(Model::eScore));
                std::string text = "HIGHSCORES\n\n";

                for (const auto& i : HighScore::getInstance().getScores()) {
                        if (i != HighScore::getInstance().getScores().back()) {
                                text.append(i->toString() + "\n");
                        }
                }
                text.append(HighScore::getInstance().getScores().back()->toString());
                high->setString(text);
                sf::FloatRect bounds = high->getLocalBounds();
                high->setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
                high->setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y - 200);
        }

        View::IView::setRainbowColor<sf::Text>(high);

        mWindow->draw(*high);
}

void Game::run()
{
        mWorld->initWorld();
        Utils::Stopwatch::getInstance().start();

        while (mWindow->isOpen()) {
                Utils::Stopwatch::getInstance().lap();
                processEvents();
                mWorld->update();
                render();
                while (!mWorld->isPlaying()) {
                        // ADD NEW SCORE
                        // RESET???
                        // HIGH-SCORE VIEW

                        mWindow->clear(sf::Color::Black);

                        drawHighScoreTable();

                        mWindow->display();
                        //                        HighScore::getInstance().add(std::make_shared<HighScoreScore>(mWorld->getScore()->getScore(),
                        //                                                                                      "Pablo"));

                        //                        mWorld = std::make_unique<World>(mFactory);
                        //                        mWorld->initWorld();
                        //                        Utils::Stopwatch::getInstance().start();
                        //                        Utils::Camera::getInstance().reset();
                }
        }
}
