//
// Created by Pablo Deputter on 09/12/2021.
//

#include "view/ScoreView.h"

#include "util/Stopwatch.h"
#include "util/Utilities.h"

using namespace View;

ScoreView::ScoreView(std::shared_ptr<Model::Score>& entity, const std::shared_ptr<sf::RenderWindow>& window)
    : IView(entity, window)
{
        // Get font associated with ScoreView associated from ResourceManager
        std::shared_ptr<sf::Font>& font = Utils::ResourceManager::getInstance().getFonts()->get(Model::eScore);
        mSprite = std::make_unique<sf::Sprite>();
        // Setup text
        mScoreText = std::make_unique<sf::Text>();
        mScoreText->setFont(*font);
        mScoreText->setFillColor(sf::Color::Black);

        mDiffText = std::make_unique<sf::Text>();
        mDiffText->setFont(*font);
        mDiffText->setCharacterSize(60);
        mDiffText->setFillColor(sf::Color::Black);

        mLevelText = std::make_unique<sf::Text>();
        mLevelText->setFont(*font);
        mLevelText->setCharacterSize(30);
        mLevelText->setFillColor(sf::Color::Black);
        mLevelText->setString("-NEW LEVEL REACHED-");
        // Position mLevelText, so it appears in the center of the screen. This text will never be modified, so
        // we don't need to dynamically update the position.
        sf::FloatRect bounds = mLevelText->getLocalBounds();
        mLevelText->setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        mLevelText->setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y - 375);
}

void ScoreView::handleEvent(const DrawEvent& event)
{
        // Update scoreText
        const unsigned int score = mEntity->getScore();
        mScoreText->setString(std::to_string(score));

        // Dynamically update position depending on size of string. Position scoreText, so it will appear at the top
        // in the center of the screen.
        auto const pos = Utils::Camera::getInstance().transform(mEntity->getX(), mEntity->getY());
        sf::FloatRect bounds = mScoreText->getLocalBounds();
        mScoreText->setPosition(sf::Vector2f(pos.first - bounds.width / 2.f, pos.second));
        // Draw mScoreText
        mWindow->draw(*mScoreText);

        // Check if difficulty text needs to be displayed
        if (Utils::Stopwatch::getInstance().checkTimer(Model::eScore)) {
                // Set rainbow-effect to difficulty text
                Utils::Utilities::setRainbowColor<sf::Text, sf::Color>(std::ref(*mDiffText));
                mWindow->draw(*mDiffText);
                mWindow->draw(*mLevelText);
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
        case Settings::eInsane:
                text = "INSANE";
                break;
        case Settings::eExtreme:
                text = "EXTREME";
                break;
        case Settings::eEasy:
                break;
        }
        // Position DiffText in the center relatively to the length of the string
        mDiffText->setString(text);
        sf::FloatRect bounds = mDiffText->getLocalBounds();
        mDiffText->setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        mDiffText->setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y - 300);
        // Start timer
        Utils::Stopwatch::getInstance().addTimer(Model::eScore, 4.5f);
}