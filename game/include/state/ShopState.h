//
// Created by Pablo Deputter on 19/12/2021.
//

#ifndef DOODLEJUMP_SHOPSTATE_H
#define DOODLEJUMP_SHOPSTATE_H

#include "Game.h"

#include "Settings.h"
#include "State.h"

#include <vector>

/**
 * @brief Namespace holds States
 */
namespace States {
/**
 * @brief Class for when in Shop
 */
class ShopState : public State
{
private:
        struct Item
        {
                std::unique_ptr<sf::Sprite> mSprite;    /**< sf::Sprite - sprite */
                std::unique_ptr<sf::Sprite> mRectangle; /**< sf::Sprite - rectangle around sprite */
                std::unique_ptr<sf::Text> mText;        /**< sf::Text - text describing item */
                /**
                 * @brief Constructor for item object
                 */
                Item()
                {
                        mSprite = std::make_unique<sf::Sprite>();
                        mRectangle = std::make_unique<sf::Sprite>();
                        mText = std::make_unique<sf::Text>();
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
                }
                /**
                 * @brief Set color to objects of Item object
                 * @param color sf::Color - color to be set
                 */
                void setColor(sf::Color color)
                {
                        mText->setFillColor(color);
                        if (color != sf::Color::White) {
                                mRectangle->setColor(sf::Color(255, 100, 100, 255));
                                return;
                        }
                        mRectangle->setColor(sf::Color(255, 255, 255, 255));
                }
        };

private:
        std::pair<unsigned int, unsigned int>
            mSelected; /**< std::pair<unsigned int,unsigned int - item selected in row and column */
        std::vector<std::vector<std::shared_ptr<Item>>> mItems; /**< 2D std::vector containing items */
        std::vector<std::shared_ptr<sf::Text>> mInfo;           /**< std::vector containing info text */
private:
        /**
         * @brief Render state
         */
        void render() const override;
        /**
         * @brief Update state
         */
        void update() override;
        /**
         * @brief Handle input
         * @param key sf::Keyboard::Key - pressed / released key
         * @param isPressed bool - is key pressed
         */
        void handleInput(sf::Keyboard::Key key, bool isPressed);
        /**
         * @brief Process events
         */
        void processEvents() override;
        /**
         * @brief Get type of State
         * @return GameStates - eShop
         */
        [[nodiscard]] unsigned int getType() const override { return eShop; }
        /**
         * @brief Create item to be viewed
         * @param text sf::Text - text to be shown
         * @param type Utils::Type - type of item to be shown
         * @param factorHorizontal float - horizontal spacing
         * @param factorVertical float - vertical spacing
         * @return Item
         */
        std::shared_ptr<Item> createItem(const std::string& text, Utils::Type type, float factorHorizontal = 1.f,
                                         float factorVertical = 1.f);

public:
        /**
         * @brief Constructor for ShopState object
         * @param window sf::RenderWindow - pointer to window where state will on draw
         * @param game Game - current game
         */
        ShopState(std::shared_ptr<sf::RenderWindow> window, Game& game);
        /**
         * @brief Destructor for ShopState object
         */
        ~ShopState() override
        {
                mItems.clear();
                mInfo.clear();
        }
};
} // namespace States

#endif // DOODLEJUMP_SHOPSTATE_H
