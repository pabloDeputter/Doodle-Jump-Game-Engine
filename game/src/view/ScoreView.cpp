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

        // Check if difficulty text needs to be displayed
        if (Utils::Stopwatch::getInstance().checkTimer(Model::eScore)) {
                // Set rainbow-effect to difficulty text
                IView::setRainbowColor<sf::Text>(mDiffText);
                mWindow->draw(*mDiffText);
        }
}

void ScoreView::handleEvent(const NewDifficultyEvent& event)
{
        std::string text = "EASY";
        switch (event.getDifficulty()) {
        case Settings::eNormal:
                text = "NORMAL";
                break;
        case Settings::eDifficult:
                text = "DIFFICULT";
                break;
        case Settings::eHard:
                text = "HARD";
                break;
        case Settings::eExtreme:
                text = "EXTREME";
                break;
        }
        // Set text and position on center of screen
        mDiffText->setString(text);
        mDiffText->setScale(1.5f, 1.5f);
        sf::FloatRect bounds = mDiffText->getLocalBounds();
        mDiffText->setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        const std::pair<float, float> windowDim = Utils::Camera::getInstance().getWindowDimensions();
        mDiffText->setPosition(mWindow->getView().getCenter());
        // Start timer
        Utils::Stopwatch::getInstance().addTimer(Model::eScore, 4.5f);
}