//
// Created by Pablo Deputter on 14/12/2021.
//

#include "state/MenuState.h"

#include "Settings.h"

#include "state/PlayState.h"
#include "state/SettingState.h"

using namespace States;
using namespace Utils;

MenuState::MenuState(std::shared_ptr<sf::RenderWindow> window, Game& game)
    : State(std::move(window), game), mSelected(0), mEnterName(false), mDiff(0)
{
        // Set title logo
        mTitle.setTexture(*Utils::ResourceManager::getInstance().getTextures()->get(Utils::Type::eMenuLogo));
        mTitle.scale(.5f, .5f);
        const auto bounds = mTitle.getLocalBounds();
        mTitle.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        mTitle.setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y * 0.15f);

        // Create scores
        createScores();

        // Create text for play again "button"
        sf::Text infoPlay;
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuInfo), sf::Color::White,
                            35, infoPlay, "PLAY");
        // Create text for clear scores "button"
        sf::Text infoClear;
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuInfo), sf::Color::White,
                            35, infoClear, "CLEAR SCORES");
        // Create text for settings "button"
        sf::Text infoSave;
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuInfo), sf::Color::White,
                            35, infoSave, "SAVE");
        // Create text for settings "button"
        sf::Text infoSettings;
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuInfo), sf::Color::White,
                            35, infoSettings, "SETTINGS");

        // Insert into std::vector
        mInfo = {infoPlay, infoClear, infoSave, infoSettings};

        // Spacing between each info displayed
        float factor_info = 1.f;
        // Positioning of info
        for (auto& i : mInfo) {
                i.setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y * 1.1f * factor_info);
                factor_info += .075f;
        }

        mSound.setBuffer(*Utils::ResourceManager::getInstance().getSounds()->get(Type::eMenuInfo));
        mSound.play();
}

void MenuState::render() const
{
        mWindow->clear(sf::Color::Black);
        // Draw title logo
        mWindow->draw(mTitle);
        // Draw scores text
        for (const auto& i : mScores) {
                mWindow->draw(i);
        }
        // Draw info text
        for (const auto& i : mInfo) {
                mWindow->draw(i);
        }
        // Display that what is drawn on screen
        mWindow->display();
}

void MenuState::update()
{
        if (!mEnterName) {
                updateInfo();
        }
}

void MenuState::handleInput(sf::Keyboard::Key key, bool isPressed)
{
        if (mEnterName && key == sf::Keyboard::Return && isPressed) {
                mEnterName = false;
        } else if (mEnterName && key != sf::Keyboard::Return) {
                return;
        } else if (!mEnterName && key == sf::Keyboard::Return && isPressed) {
                onSelect();
        } else if (key == sf::Keyboard::Up && isPressed) {
                if (mSelected == 0) {
                        mSelected = mInfo.size() - 1;
                } else {
                        mSelected--;
                }
                // If we go over the index of the last element we will get a segmentation fault, so we set
                // mSelected equal to zero.
        } else if (key == sf::Keyboard::Down && isPressed) {
                mSelected++;
                // If mSelected is equal we and we want to decrease the value of it, it shall point to a non-existing
                // element inside mInfo, so we set mSelected equal to the index of the last element.
                if (mSelected > mInfo.size() - 1) {
                        mSelected = 0;
                }
        }
}

void MenuState::processEvents()
{
        sf::Event event{};
        while (mWindow->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::TextEntered:
                        if (mEnterName) {
                                if (event.text.unicode < 128) {
                                        mName += static_cast<char>(event.text.unicode);
                                        HighScore::getInstance().changeName(mName, mIndex);
                                        updateScoreName();
                                }
                                break;
                        }
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

void MenuState::createScores()
{
        // Clear scores
        mScores.clear();
        // Create text for the scores
        float factor_a = 2.f;
        const auto& scores_vector = HighScore::getInstance().getScores();
        for (const auto& i : scores_vector) {
                sf::Text a;
                // Initialize and style Score
                Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuHighScores),
                                    sf::Color::White, 20, a, i->toString());
                a.setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y * 0.15f * factor_a);
                mScores.emplace_back(a);
                factor_a += 0.5f;
        }
        // Set colors
        if (!mScores.empty()) {
                mScores[0].setFillColor(sf::Color(204, 46, 30));
        }
        if (mScores.size() >= 2) {
                mScores[1].setFillColor(sf::Color(250, 160, 58));
        }
        if (mScores.size() >= 3) {
                mScores[2].setFillColor(sf::Color(251, 240, 80));
        }
        if (mScores.size() >= 4) {
                mScores[3].setFillColor(sf::Color(113, 246, 75));
        }
        if (mScores.size() >= 5) {
                mScores[4].setFillColor(sf::Color(90, 196, 250));
        }
        for (unsigned int i = 5; i < mScores.size(); i++) {
                if (mScores.size() >= i) {
                        mScores[i].setFillColor(sf::Color(150, 30, 150));
                } else {
                        break;
                }
        }
}

void MenuState::updateScoreName()
{
        // Get score to update
        sf::Text& toUpdate = mScores[mIndex];
        // Update string
        toUpdate.setString(HighScore::getInstance().getScores()[mIndex]->toString());
        // Update position
        const auto bounds = toUpdate.getLocalBounds();
        toUpdate.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}

void MenuState::updateInfo()
{
        // Set color of every sf::Text info to white
        for (auto& i : mInfo) {
                i.setFillColor(sf::Color::White);
        }
        // Highlight selected info to RED
        mInfo[mSelected].setFillColor(sf::Color(204, 46, 30));
}

void MenuState::onSelect()
{
        if (mSelected == 0) {
                mGame.pushState(std::make_shared<PlayState>(
                    std::make_unique<World>(mGame.getFactory(), true, Settings::Difficulty(mDiff)), mWindow, mGame));
        } else if (mSelected == 1) {
                // Clear high scores
                HighScore::getInstance().clear();
                // Update scores
                createScores();
        } else if (mSelected == 2) {
                // Save high scores - get saved anyways when closing app
                HighScore::getInstance().save();
        } else if (mSelected == 3) {
                // Push SettingState on stack
                mGame.pushState(std::make_shared<SettingState>(mWindow, mGame, Settings::Difficulty(mDiff)));
        }
}

void MenuState::newHighScore()
{
        mName.clear();
        // Get achieved score
        const int achievedScore = HighScore::getInstance().getToAdd();
        // New high score achieved
        if (achievedScore != 0) {
                mIndex = HighScore::getInstance().add(std::make_shared<HighScoreData>(achievedScore, "ENTER NAME"));
                mEnterName = true;
                createScores();
        }
}
