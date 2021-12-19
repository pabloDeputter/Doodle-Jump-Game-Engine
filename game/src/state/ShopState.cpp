//
// Created by Pablo Deputter on 19/12/2021.
//

#include "state/ShopState.h"

#include "util/Utilities.h"

#include <utility>

using namespace States;
using namespace Utils;

std::shared_ptr<ShopState::Item> ShopState::createItem(const std::string& text, Utils::Type type,
                                                       float factorHorizontal, float factorVertical)
{
        // Create new item
        std::shared_ptr<Item> item = std::make_shared<Item>();

        // Initialize background rectangle
        item->mRectangle->setTexture(*Utils::ResourceManager::getInstance().getTextures()->get(Type::eMenuItemBack));
        item->mRectangle->scale(.75, .75);

        // Initialize sprite
        const auto& tex = *Utils::ResourceManager::getInstance().getTextures()->get(type);
        const auto texSize = tex.getSize();
        item->mSprite->setTexture(tex);
        item->mSprite->scale(sf::Vector2f(75.f / (float)texSize.x, 75.f / (float)texSize.y));

        // Initialize text
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuSettings),
                            sf::Color::White, 30, *item->mText, text);

        // Positioning rectangle
        const auto boundsRectangle = item->mRectangle->getLocalBounds();
        item->mRectangle->setOrigin(boundsRectangle.left + boundsRectangle.width / 2.f,
                                    boundsRectangle.top + boundsRectangle.height / 2.f);
        item->mRectangle->setPosition((float)mWindow->getSize().x * 0.25f * factorHorizontal,
                                      (float)mWindow->getSize().y * 0.20f * factorVertical);
        const auto posRectangle = item->mRectangle->getPosition();

        // Positioning sprite
        const auto boundsSprite = item->mSprite->getLocalBounds();
        item->mSprite->setOrigin(boundsSprite.left + boundsSprite.width / 2.f,
                                 boundsSprite.top + boundsSprite.height / 2.f);
        item->mSprite->setPosition(posRectangle.x, posRectangle.y * 1.02f);

        // Positioning text
        const auto boundsText = item->mText->getLocalBounds();
        item->mText->setOrigin(boundsText.left + boundsText.width / 2.f, boundsText.top + boundsText.height / 2.f);
        item->mText->setPosition(posRectangle.x, posRectangle.y + boundsRectangle.height * .50f);

        return item;
}

ShopState::ShopState(std::shared_ptr<sf::RenderWindow> window, Game& game)
    : State(std::move(window), game), mSelected({0, 0})
{
        // Initialize std::vector with 2 rows and 3 columns
        mItems = std::vector(2, std::vector<std::shared_ptr<Item>>(3, nullptr));
        // Create character items, first row
        mItems[0][0] = createItem("FROGGY", Utils::eShopCh1, 1.f);
        mItems[0][1] = createItem("CHAINSAW MAN", Utils::eShopCh2, 2.f);
        mItems[0][2] = createItem("KIRBY", Utils::eShopCh3, 3.f);

        // Create background items, second row
        mItems[1][0] = createItem("CLOUDS", Utils::eShopBg1, 1.f, 2.5f);
        mItems[1][1] = createItem("PURPLE", Utils::eShopBg2, 2.f, 2.5f);
        mItems[1][2] = createItem("LAVA", Utils::eShopBg3, 3.f, 2.5f);

        // Create info text
        std::shared_ptr<sf::Text> textCh = std::make_shared<sf::Text>();
        std::shared_ptr<sf::Text> textBg = std::make_shared<sf::Text>();
        // Initialize text
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuSettings),
                            sf::Color::White, 40, *textCh, "- CHARACTERS -");
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuSettings),
                            sf::Color::White, 40, *textBg, "- BACKGROUNDS -");
        // Position text
        textCh->setPosition((float)mWindow->getSize().x / 2.f, mItems[0][0]->mRectangle->getPosition().y * .5f);
        textBg->setPosition((float)mWindow->getSize().x / 2.f, mItems[1][0]->mRectangle->getPosition().y * .80f);
        mInfo = {textCh, textBg};
}

void ShopState::render() const
{
        mWindow->clear(sf::Color::Black);
        for (const auto& i : mItems) {
                for (const auto& j : i) {
                        j->draw(mWindow);
                }
        }
        for (const auto& i : mInfo) {
                mWindow->draw(*i);
        }
        mWindow->display();
}

void ShopState::update()
{
        // Set color of every sf::Text setting to white
        for (auto& i : mItems) {
                for (auto& j : i) {
                        j->setColor(sf::Color::White);
                }
        }
        // Highlight selected setting to RED
        mItems[mSelected.first][mSelected.second]->setColor(sf::Color(204, 46, 30));
}

void ShopState::handleInput(sf::Keyboard::Key key, bool isPressed)
{
        if (key == sf::Keyboard::Escape && isPressed) {
                mGame.popState();
        } else if (key == sf::Keyboard::Return && isPressed) {
                // Chosen character
                if (mSelected.first == 0) {
                        if (mSelected.second == 0) {
                                Utils::ResourceManager::getInstance().setTexture(Utils::eShopCh1, Utils::ePlayer);
                        } else if (mSelected.second == 1) {
                                Utils::ResourceManager::getInstance().setTexture(Utils::eShopCh2, Utils::ePlayer);
                        } else if (mSelected.second == 2) {
                                Utils::ResourceManager::getInstance().setTexture(Utils::eShopCh3, Utils::ePlayer);
                        }

                }
                // Chosen background
                else if (mSelected.first == 1) {
                        if (mSelected.second == 0) {
                                Utils::ResourceManager::getInstance().setTexture(Utils::eShopBg1, Utils::eBackground);
                        } else if (mSelected.second == 1) {
                                Utils::ResourceManager::getInstance().setTexture(Utils::eShopBg2, Utils::eBackground);
                        } else if (mSelected.second == 2) {
                                Utils::ResourceManager::getInstance().setTexture(Utils::eShopBg3, Utils::eBackground);
                        }
                }
        } else if (key == sf::Keyboard::Right && isPressed) {
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
