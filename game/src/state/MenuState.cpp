//
// Created by Pablo Deputter on 14/12/2021.
//

#include "state/PlayState.h"

using namespace States;

MenuState::MenuState(std::shared_ptr<sf::RenderWindow> window, Game& game) : State(std::move(window), game)
{
        mTitle.setFont(*Utils::ResourceManager::getInstance().getFonts()->get(Model::eScore));
        mTitle.setFillColor(sf::Color::Cyan);
        mTitle.setCharacterSize(30);
        mTitle.setString("-HIGH SCORES-");
        sf::FloatRect bounds = mTitle.getLocalBounds();
        mTitle.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        mTitle.setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y - 600);

        mScores.setFont(*mTitle.getFont());
        mScores.setFillColor(sf::Color::White);
        mScores.setLineSpacing(2.f);
        mScores.setCharacterSize(25);

        std::string text;
        const auto& scores_vector = HighScore::getInstance().getScores();
        for (const auto& i : scores_vector) {
                if (i != scores_vector.back()) {
                        text.append(i->toString() + "\n");
                }
        }
        if (!scores_vector.empty()) {
                text.append(scores_vector.back()->toString());
        }

        mScores.setString(text);
        bounds = mScores.getLocalBounds();
        mScores.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        mScores.setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y - 300);

        mHighScore = mScores;
        mHighScore.setString(scores_vector[0]->toString());

        mInfo = mScores;
        mInfo.setCharacterSize(20);
        mInfo.setString("Press 'r' to start a new game!\n Press 'c' to wipe high-scores!");
        bounds = mInfo.getLocalBounds();
        mInfo.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        mInfo.setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y + 100);
}

void MenuState::render() const
{
        mWindow->clear(sf::Color::Black);
        mWindow->draw(mTitle);
        mWindow->draw(mScores);
        mWindow->draw(mHighScore);
        mWindow->draw(mInfo);
        mWindow->display();
}

void MenuState::update()
{

        Utils::Utilities::setRainbowColor<sf::Text, sf::Color>(mTitle);
        Utils::Utilities::setRainbowColor<sf::Text, sf::Color>(mHighScore);
}

void MenuState::handleInput(sf::Keyboard::Key key, bool isPressed) const
{
        if (key == sf::Keyboard::C && isPressed) {
                HighScore::getInstance().clear();
        }
}

void MenuState::processEvents()
{
        sf::Event event;
        while (mWindow->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::R) {
                                mGame.mStateType = ePlay;
                                return;
                        }
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