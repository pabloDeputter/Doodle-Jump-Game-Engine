//
// Created by Pablo Deputter on 14/12/2021.
//

#ifndef DOODLEJUMP_MENUSTATE_H
#define DOODLEJUMP_MENUSTATE_H

#include "HighScore.h"
#include "State.h"
#include "util/Resourcemanager.h"
#include "util/Utilities.h"

#include "Game.h"

#include <utility>

class MenuState : public State
{
private:
        sf::Text mTitle;
        sf::Text mScores;
        sf::Text mHighScore;
        sf::Text mInfo;

private:
        void render() override
        {
                mWindow->clear(sf::Color::Black);
                mWindow->draw(mTitle);
                mWindow->draw(mScores);
                mWindow->draw(mHighScore);
                mWindow->draw(mInfo);
                mWindow->display();
        }

        void update() override
        {

                Utils::Utilities::setRainbowColor<sf::Text, sf::Color>(mTitle);
                Utils::Utilities::setRainbowColor<sf::Text, sf::Color>(mHighScore);
        }

        void handleInput(sf::Keyboard::Key key, bool isPressed) const;

        void processEvents() override;

public:
        MenuState(std::shared_ptr<sf::RenderWindow> window, Game& game) : State(std::move(window), game)
        {
                mTitle.setFont(*Utils::Resourcemanager::getInstance().getFonts()->get(Model::eScore));
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

        ~MenuState() override = default;

        [[nodiscard]] unsigned int getType() override { return eMenu; }
};

#endif // DOODLEJUMP_MENUSTATE_H
