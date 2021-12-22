//
// Created by Pablo Deputter on 22/12/2021.
//

#ifndef DOODLEJUMP_ITEM_H
#define DOODLEJUMP_ITEM_H

#include "State.h"
#include "util/Utilities.h"

using namespace Utils;

namespace States {
/**
 * @brief Struct for ShopState item, can be a character or background that is unlock-able
 */
struct Item
{
        std::unique_ptr<sf::Sprite> mSprite;    /**< sf::Sprite - sprite */
        std::unique_ptr<sf::Sprite> mRectangle; /**< sf::Sprite - rectangle around sprite */
        std::unique_ptr<sf::Text> mText;        /**< sf::Text - text describing item */
        std::unique_ptr<sf::Text> mCostText;    /**< sf::Text - cost of item text */
        int mCost;                              /**< int - cost of item */
        unsigned int mType;                     /**< unsigned int - type of Item to find matching texture */
        bool mUnlocked;                         /**< bool - is item already unlocked */

        /**
         * @brief Constructor for item object
         */
        Item()
        {
                mSprite = std::make_unique<sf::Sprite>();
                mRectangle = std::make_unique<sf::Sprite>();
                mText = std::make_unique<sf::Text>();
                mCostText = std::make_unique<sf::Text>();
                mCost = 0;
                mType = 0;
                mUnlocked = false;
        }
        /**
         * @brief Create item to be viewed
         * @param text sf::Text - text to be shown
         * @param cost int - cost of item
         * @param unlocked bool - is item already unlocked by Player
         * @param type Utils::Type - type of item to be shown, used to get the right texture to show in Shop
         * @param factorHorizontal float - horizontal spacing
         * @param factorVertical float - vertical spacing
         * @param window sf::RenderWindow - window where Item will be rendered on
         */
        Item(const std::string& text, int cost, bool unlocked, Utils::Type type, float factorHorizontal,
             float factorVertical, const std::shared_ptr<sf::RenderWindow>& window)
        {
                mCost = cost;
                mUnlocked = unlocked;
                mType = type;

                mSprite = std::make_unique<sf::Sprite>();
                mRectangle = std::make_unique<sf::Sprite>();
                mText = std::make_unique<sf::Text>();
                mCostText = std::make_unique<sf::Text>();

                // Initialize background rectangle
                mRectangle->setTexture(*Utils::ResourceManager::getInstance().getTextures()->get(Type::eMenuItemBack));
                mRectangle->scale(.75, .75);

                // Initialize sprite
                const auto& tex = *Utils::ResourceManager::getInstance().getTextures()->get(type);
                const auto texSize = tex.getSize();
                mSprite->setTexture(tex);
                mSprite->scale(sf::Vector2f(75.f / (float)texSize.x, 75.f / (float)texSize.y));

                // Initialize text
                Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuInfo),
                                    sf::Color::White, 30, *mText, text);
                Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuInfo),
                                    sf::Color(255, 215, 0), 28, *mCostText, std::to_string(cost));

                // Positioning rectangle
                const auto boundsRectangle = mRectangle->getLocalBounds();
                mRectangle->setOrigin(boundsRectangle.left + boundsRectangle.width / 2.f,
                                      boundsRectangle.top + boundsRectangle.height / 2.f);
                mRectangle->setPosition((float)window->getSize().x * 0.25f * factorHorizontal,
                                        (float)window->getSize().y * 0.20f * factorVertical);
                const auto posRectangle = mRectangle->getPosition();

                // Positioning sprite
                const auto boundsSprite = mSprite->getLocalBounds();
                mSprite->setOrigin(boundsSprite.left + boundsSprite.width / 2.f,
                                   boundsSprite.top + boundsSprite.height / 2.f);
                mSprite->setPosition(posRectangle.x, posRectangle.y * 1.02f);

                // Positioning text
                const auto boundsText = mText->getLocalBounds();
                mText->setOrigin(boundsText.left + boundsText.width / 2.f, boundsText.top + boundsText.height / 2.f);
                mText->setPosition(posRectangle.x, posRectangle.y + boundsRectangle.height * .50f);

                const auto boundsCost = mCostText->getLocalBounds();
                mCostText->setOrigin(boundsCost.left + boundsCost.width / 2.f,
                                     boundsCost.top + boundsCost.height / 2.f);
                mCostText->setPosition(posRectangle.x, posRectangle.y + boundsRectangle.height * .65f);
        }
        /**
         * @brief Destructor for Item object
         */
        ~Item() = default;
        /**
         * @brief Draw all object
         * @param window sf::RenderWindow - window where objects are drawn on
         */
        void draw(const std::shared_ptr<sf::RenderWindow>& window) const
        {
                window->draw(*mRectangle);
                window->draw(*mSprite);
                window->draw(*mText);
                window->draw(*mCostText);
        }
        /**
         * @brief Set color to objects of Item object
         * @param color sf::Color - color to be set
         * @param coins int - amount of coins Player has available
         */
        void setColor(sf::Color color, int coins) const
        {
                mText->setFillColor(color);
                // GREEN
                if (mUnlocked) {
                        mRectangle->setColor(sf::Color(13, 131, 4, 255));
                }
                // ORANGE
                else if (!mUnlocked && coins >= mCost) {
                        mRectangle->setColor(sf::Color(255, 145, 0, 255));
                }
                // RED
                else {
                        mRectangle->setColor(sf::Color(255, 100, 100, 255));
                }
        }
};
} // namespace States

#endif // DOODLEJUMP_ITEM_H
