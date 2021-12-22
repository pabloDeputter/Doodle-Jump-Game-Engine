//
// Created by Pablo Deputter on 15/12/2021.
//

#include "state/PlayState.h"

using namespace States;

PlayState::PlayState(std::unique_ptr<World> world, std::shared_ptr<sf::RenderWindow> window, Game& game)
    : State(std::move(window), game), mWorld(std::move(world))
{
        // Reset Camera and Stopwatch
        Utils::Camera::getInstance().reset();
        Utils::Stopwatch::getInstance().reset();
        // Initialize World
        mWorld->initWorld();
}

void PlayState::render() const
{
        mWindow->clear(sf::Color::White);
        mWorld->render();
        mWindow->display();
}

void PlayState::update()
{
        // Update world
        mWorld->update();
        // If Player is dead
        if (!mWorld->isPlaying()) {
                const int score = mWorld->getScore()->getScore();
                const int coins = mWorld->getScore()->getCoins();
                // Push ePlayState off gameState stack
                mGame.popState();
                // Add score to HighScore buffer if it is a new high score and switch game state
                // to eMenuState state. If no new high score was achieved we switch directly to
                // the eMenu state.
                if (HighScore::getInstance().isHighScore(score)) {
                        HighScore::getInstance().add(score);
                        mGame.peekState()->newHighScore(coins);
                }
        }
}

void PlayState::handleInput(sf::Keyboard::Key key, bool isPressed) const
{
        if (key == sf::Keyboard::Z) {
                mWorld->events("Z", isPressed);
        } else if (key == sf::Keyboard::S) {
                mWorld->events("S", isPressed);
        } else if (key == sf::Keyboard::A) {
                mWorld->events("A", isPressed);
        } else if (key == sf::Keyboard::D) {
                mWorld->events("D", isPressed);
        } else if (key == sf::Keyboard::Space) {
                mWorld->events("SPACE", isPressed);
        }
}

void PlayState::processEvents()
{
        sf::Event event{};
        while (mWindow->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::KeyPressed:
                        handleInput(event.key.code, true);
                        break;
                case sf::Event::KeyReleased:
                        handleInput(event.key.code, false);
                        break;
                case sf::Event::Closed:
                        mWindow->close();
                        break;
                }
        }
}