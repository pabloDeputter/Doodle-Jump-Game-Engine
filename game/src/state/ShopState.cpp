//
// Created by Pablo Deputter on 19/12/2021.
//

#include "state/ShopState.h"

#include "util/Utilities.h"

#include <utility>

using namespace States;
using namespace Utils;

ShopState::ShopState(std::shared_ptr<sf::RenderWindow> window, Game& game,
                     std::vector<std::vector<std::shared_ptr<Item>>> items, int& coins)
    : State(std::move(window), game), mSelected({0, 0}), mBuying(false), mCoins(coins)
{
        // Generate items
        mItems = std::move(items);

        // Create info text
        std::shared_ptr<sf::Text> textCh = std::make_shared<sf::Text>();
        std::shared_ptr<sf::Text> textBg = std::make_shared<sf::Text>();
        // Initialize text
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuInfo), sf::Color::White,
                            40, *textCh, "- CHARACTERS -");
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuInfo), sf::Color::White,
                            40, *textBg, "- BACKGROUNDS -");
        // Position text
        textCh->setPosition((float)mWindow->getSize().x / 2.f, mItems[0][0]->mRectangle->getPosition().y * .5f);
        textBg->setPosition((float)mWindow->getSize().x / 2.f, mItems[1][0]->mRectangle->getPosition().y * .82f);
        mInfo = {textCh, textBg};

        // Create text for coins
        mCoinsText = std::make_unique<sf::Text>();
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuInfo),
                            sf::Color(255, 215, 0), 45, *mCoinsText, "COINS: " + std::to_string(mCoins));
        mCoinsText->setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y * 1.6f);

        // Create text for when Item is bought
        mBuyingText = std::make_unique<sf::Text>();
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuInfo),
                            sf::Color(204, 46, 30), 35, *mBuyingText, "LOL");
        mBuyingText->setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y * 1.75f);
}

void ShopState::render() const
{
        mWindow->clear(sf::Color::Black);
        // Render all items
        for (const auto& i : mItems) {
                for (const auto& j : i) {
                        j->draw(mWindow);
                }
        }
        // Render info sf::Text
        for (const auto& i : mInfo) {
                mWindow->draw(*i);
        }
        // Render available coins
        mWindow->draw(*mCoinsText);
        // If we are in a buying state --> draw sf::Text for buying
        if (mBuying) {
                mWindow->draw(*mBuyingText);
        }
        mWindow->display();
}

void ShopState::update()
{
        // Set color of every sf::Text or texture setting according color:
        // WHITE - text
        // GREEN - unlocked
        // RED - not yet unlocked
        // ORANGE - unlock-able
        for (auto& i : mItems) {
                for (auto& j : i) {
                        j->setColor(sf::Color::White, mCoins);
                }
        }
        // Highlight selected setting to RED
        mItems[mSelected.first][mSelected.second]->setColor(sf::Color(204, 46, 30), mCoins);

        mCoinsText->setString("COINS: " + std::to_string(mCoins));
        // Update position
        const auto boundCoins = mCoinsText->getLocalBounds();
        mCoinsText->setOrigin(boundCoins.left + boundCoins.width / 2.f, boundCoins.top + boundCoins.height / 2.f);
}

void ShopState::handleInput(sf::Keyboard::Key key, bool isPressed)
{
        if (key == sf::Keyboard::Escape && isPressed) {
                // In buying state of Item
                if (mBuying) {
                        mBuying = false;
                }
                // Pop ShopState of stack
                else {
                        mGame.popState();
                }
        } else if (key == sf::Keyboard::Return && isPressed) {
                // Selected Item
                const auto& selectedItem = mItems[mSelected.first][mSelected.second];
                // In state of buying of an Item
                if (mBuying) {
                        mBuying = false;
                        // If Player has enough coins it can buy the new Item
                        if (mCoins > selectedItem->mCost) {
                                selectedItem->mUnlocked = true;
                                mCoins -= selectedItem->mCost;
                                selectItem();
                        }
                }

                // Chosen item is already unlocked
                else if (selectedItem->mUnlocked) {
                        selectItem();
                }
                // Chosen item is not yet unlocked
                else {
                        mBuying = true;
                        // Player has enough coins to buy Item
                        if (mCoins > selectedItem->mCost) {
                                mBuyingText->setString("Buying " + selectedItem->mText->getString() + " for " +
                                                       std::to_string(selectedItem->mCost) + " coins...");
                        }
                        // Player has not enough coins to buy Item
                        else {
                                mBuyingText->setString("Not enough coins for " + selectedItem->mText->getString() +
                                                       " ...");
                        }
                        // Update position
                        const auto bounds = mBuyingText->getLocalBounds();
                        mBuyingText->setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
                }
        }
        // Move around in menu with arrow keys
        else if (!mBuying) {
                menuMove(key, isPressed);
        }
}

void ShopState::selectItem()
{
        // Chosen character
        if (mSelected.first == 0) {
                if (mSelected.second == 0 && mItems[0][0]->mUnlocked) {
                        Utils::ResourceManager::getInstance().setTexture(Utils::eShopCh1, Utils::ePlayer);
                } else if (mSelected.second == 1 && mItems[0][1]->mUnlocked) {
                        Utils::ResourceManager::getInstance().setTexture(Utils::eShopCh2, Utils::ePlayer);
                } else if (mSelected.second == 2 && mItems[0][1]->mUnlocked) {
                        Utils::ResourceManager::getInstance().setTexture(Utils::eShopCh3, Utils::ePlayer);
                }

        }
        // Chosen background
        else if (mSelected.first == 1) {
                if (mSelected.second == 0 && mItems[1][0]->mUnlocked) {
                        Utils::ResourceManager::getInstance().setTexture(Utils::eShopBg1, Utils::eBackground);
                } else if (mSelected.second == 1 && mItems[1][1]->mUnlocked) {
                        Utils::ResourceManager::getInstance().setTexture(Utils::eShopBg2, Utils::eBackground);
                } else if (mSelected.second == 2 && mItems[1][2]->mUnlocked) {
                        Utils::ResourceManager::getInstance().setTexture(Utils::eShopBg3, Utils::eBackground);
                }
        }
}

void ShopState::menuMove(sf::Keyboard::Key key, bool isPressed)
{
        if (key == sf::Keyboard::Right && isPressed) {
                mSelected.second++;
                if (mSelected.second > mItems[mSelected.first].size() - 1) {
                        mSelected.second = 0;
                }
        } else if (key == sf::Keyboard::Left && isPressed) {
                if (mSelected.second == 0) {
                        mSelected.second = mItems[mSelected.first].size() - 1;
                } else {
                        mSelected.second--;
                }
        } else if (key == sf::Keyboard::Up && isPressed) {
                if (mSelected.first == 0) {
                        mSelected.first = mItems.size() - 1;
                } else {
                        mSelected.first--;
                }
        } else if (key == sf::Keyboard::Down && isPressed) {
                mSelected.first++;
                if (mSelected.first > mItems.size() - 1) {
                        mSelected.first = 0;
                }
        }
}

void ShopState::processEvents()
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
