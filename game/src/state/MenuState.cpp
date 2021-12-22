//
// Created by Pablo Deputter on 14/12/2021.
//

#include "state/MenuState.h"

#include "Settings.h"

#include "state/PlayState.h"
#include "state/SettingState.h"
#include "state/ShopState.h"

using namespace States;
using namespace Utils;

MenuState::MenuState(std::shared_ptr<sf::RenderWindow> window, Game& game)
    : State(std::move(window), game), mSelected(0), mIndex(0), mEnterName(false), mDiff(0), mCoins(0),
      mPath("resource/config.json")
{
        // Set title logo
        mTitle = std::make_unique<sf::Sprite>();
        mTitle->setTexture(*Utils::ResourceManager::getInstance().getTextures()->get(Utils::Type::eMenuLogo));
        mTitle->scale(.5f, .5f);
        const auto bounds = mTitle->getLocalBounds();
        mTitle->setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        mTitle->setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y * 0.15f);

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
                            35, infoSave, "SAVE SCORES");
        // Create text for settings "button"
        sf::Text infoSettings;
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuInfo), sf::Color::White,
                            35, infoSettings, "SETTINGS");
        // Create text for music "button
        sf::Text infoMusic;
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuInfo), sf::Color::White,
                            35, infoMusic, "PAUSE MUSIC");
        // Create text for shop "button"
        sf::Text infoShop;
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuInfo), sf::Color::White,
                            35, infoShop, "SHOP");

        // Insert into std::vector
        mInfo = {std::make_unique<sf::Text>(infoPlay),  std::make_unique<sf::Text>(infoClear),
                 std::make_unique<sf::Text>(infoSave),  std::make_unique<sf::Text>(infoSettings),
                 std::make_unique<sf::Text>(infoMusic), std::make_unique<sf::Text>(infoShop)};

        // Spacing between each info displayed
        float factor_info = 1.f;
        // Positioning of info
        for (auto& i : mInfo) {
                i->setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y * 1.1f * factor_info);
                factor_info += .075f;
        }

        // Open file as input
        json j;
        std::ifstream file(mPath);
        // If file can't be opened, throw exception and return
        if (!file.is_open()) {
                throw(Utils::FileException(std::move(mPath), "ConfigFile"));
                return;
        }
        // Read data into json
        file >> j;
        // Close file
        file.close();
        // Find coins in json
        mCoins = j["coins"];

        // Create text for coins
        mCoinsText = std::make_unique<sf::Text>();
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuInfo),
                            sf::Color(255, 215, 0), 45, *mCoinsText, "COINS: " + std::to_string(mCoins));
        mCoinsText->setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y * 1.6f);

        // Initialize std::vector of Items with 2 rows and 3 columns
        mItems = std::vector(2, std::vector<std::shared_ptr<Item>>(3, nullptr));
        // Lambda function to generate Items from json file
        auto fillItems = [this, j](const std::string& id, unsigned int row, float horizontalSpacing = 1.f,
                                   const float verticalSpacing = 1.f) -> void {
                const auto& array = j[id];
                auto it = std::begin(array);
                unsigned int column = 0;
                while (it != std::end(array)) {
                        Utils::Type type((*it)["type"]);
                        mItems[row][column] = std::make_shared<Item>((*it)["name"], (*it)["cost"], (*it)["unlocked"],
                                                                     type, horizontalSpacing, verticalSpacing, mWindow);
                        column++;
                        horizontalSpacing += 1.f;
                        it++;
                }
        };
        fillItems("characters", 0, 1.f);
        fillItems("backgrounds", 1, 1.f, 2.7);

        // Sound that will be playing until it is paused or window i closed
        mSound = std::make_unique<sf::Sound>();
        mSound->setBuffer(*Utils::ResourceManager::getInstance().getSounds()->get(Type::eMenuInfo));
        mSound->setVolume(15.f);
        mSound->setLoop(true);
        mSound->play();
}

void MenuState::render() const
{
        mWindow->clear(sf::Color::Black);
        // Draw title logo
        mWindow->draw(*mTitle);
        // Draw scores text
        for (const auto& i : mScores) {
                mWindow->draw(*i);
        }
        // Draw info text
        for (const auto& i : mInfo) {
                mWindow->draw(*i);
        }
        mWindow->draw(*mCoinsText);
        // Display that what is drawn on screen
        mWindow->display();
}

void MenuState::update()
{
        if (!mEnterName) {
                updateInfo();
        }
        mCoinsText->setString("COINS: " + std::to_string(mCoins));
        // Update position
        const auto boundCoins = mCoinsText->getLocalBounds();
        mCoinsText->setOrigin(boundCoins.left + boundCoins.width / 2.f, boundCoins.top + boundCoins.height / 2.f);
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
                mScores.emplace_back(std::make_unique<sf::Text>(a));
                factor_a += 0.5f;
        }
        // Set colors
        if (!mScores.empty()) {
                mScores[0]->setFillColor(sf::Color(204, 46, 30));
        }
        if (mScores.size() >= 2) {
                mScores[1]->setFillColor(sf::Color(250, 160, 58));
        }
        if (mScores.size() >= 3) {
                mScores[2]->setFillColor(sf::Color(251, 240, 80));
        }
        if (mScores.size() >= 4) {
                mScores[3]->setFillColor(sf::Color(113, 246, 75));
        }
        if (mScores.size() >= 5) {
                mScores[4]->setFillColor(sf::Color(90, 196, 250));
        }
        for (unsigned int i = 5; i < mScores.size(); i++) {
                if (mScores.size() >= i) {
                        mScores[i]->setFillColor(sf::Color(150, 30, 150));
                } else {
                        break;
                }
        }
}

void MenuState::updateScoreName()
{
        // Get score to update
        const auto& toUpdate = mScores[mIndex];
        // Update string
        toUpdate->setString(HighScore::getInstance().getScores()[mIndex]->toString());
        // Update position
        const auto bounds = toUpdate->getLocalBounds();
        toUpdate->setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}

void MenuState::updateInfo()
{
        // Set color of every sf::Text info to white
        for (auto& i : mInfo) {
                i->setFillColor(sf::Color::White);
        }
        // Highlight selected info to RED
        mInfo[mSelected]->setFillColor(sf::Color(204, 46, 30));
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
        } else if (mSelected == 4) {
                // Get selected sf::Text, what is that one for Music
                auto& selected = mInfo[mSelected];
                // Is music was playing, we pause it and change sf::Text to "RESUME MUSIC"
                if (mSound->getStatus() == sf::Sound::Playing) {
                        mSound->pause();
                        selected->setString("RESUME MUSIC");
                }
                // Is music was paused, we let it play and change sf::Text to "PAUSE MUSIC"
                else {
                        mSound->play();
                        selected->setString("PAUSE MUSIC");
                }
                // Update position
                const auto boundMusic = selected->getLocalBounds();
                selected->setOrigin(boundMusic.left + boundMusic.width / 2.f, boundMusic.top + boundMusic.height / 2.f);
        } else if (mSelected == 5) {
                // Push ShopState on stack
                mGame.pushState(std::make_shared<ShopState>(mWindow, mGame, mItems, mCoins));
        }
}

void MenuState::newHighScore(int coins)
{
        mName.clear();
        // Get achieved score
        const int achievedScore = HighScore::getInstance().getToAdd();
        // New high score achieved
        if (achievedScore != 0) {
                mIndex = HighScore::getInstance().add(std::make_shared<HighScoreData>(achievedScore, "ENTER NAME"));
                std::cout << mIndex << "\n";
                mEnterName = true;
                createScores();
        }
        mCoins += coins;
        mCoinsText->setString("COINS: " + std::to_string(mCoins));
        // Update position
        mCoinsText->setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y * 1.6f);
}

void MenuState::save(json& j) const
{
        // Save coins to json
        j["coins"] = mCoins;

        // Save items to json
        auto createJson = [](const std::string& id, const std::vector<std::shared_ptr<Item>>& items, json& toAdd) {
                // Create new json array
                json array = json::array();
                for (const auto& i : items) {
                        // Create new element
                        json item;
                        item["name"] = i->mText->getString();
                        item["cost"] = i->mCost;
                        item["unlocked"] = i->mUnlocked;
                        item["type"] = i->mType;
                        array.emplace_back(item);
                }
                toAdd[id] = array;
        };
        // Create array for character items
        createJson("characters", mItems[0], j);
        // Create array for background items
        createJson("backgrounds", mItems[1], j);

        // Save json to file
        std::ofstream file(mPath);
        file << j.dump(4);
        file.close();
}