//
// Created by Pablo Deputter on 09/12/2021.
//

#include "view/ScoreView.h"

using namespace View;

void ScoreView::handleEvent(const DrawEvent& event)
{
        const unsigned int score = mEntity->getScore();
        mText->setString(std::to_string(score));

        auto const pos = Utils::Camera::getInstance().transform(mEntity->getX(), mEntity->getY());

        sf::FloatRect bounds = mText->getLocalBounds();
        mText->setPosition(sf::Vector2f(pos.first - bounds.width / 2.f, pos.second));

        mWindow->draw(*mText);

        if (Utils::Stopwatch::getInstance().checkTimer(Model::eScore)) {

                mWindow->draw(*mDiffText);
        }
}

void ScoreView::handleEvent(const NewDifficultyEvent& event)
{
        std::string text = "EASY";
        switch (event.getDifficulty()) {
        case Settings::eNormal:
                text = "NORMAL";
                mDiffText->setFillColor(sf::Color::Black);
                break;
        case Settings::eDifficult:
                text = "DIFFICULT";
                mDiffText->setFillColor(sf::Color::Magenta);
                break;
        case Settings::eHard:
                text = "HARD";
                mDiffText->setFillColor(sf::Color(255, 165, 0));
                break;
        case Settings::eExtreme:
                text = "EXTREME";
                mDiffText->setFillColor(sf::Color::Red);
                break;
        }
        // TODO - position
        mDiffText->setString(text);
        mDiffText->setScale(1.5f, 1.5f);
        mDiffText->setPosition(sf::Vector2f(400, 400));
        sf::FloatRect bounds = mDiffText->getLocalBounds();
        mDiffText->setPosition(sf::Vector2f(bounds.width - bounds.left / 2.f, mDiffText->getPosition().y));
        Utils::Stopwatch::getInstance().addTimer(Model::eScore, 3.5f);
}