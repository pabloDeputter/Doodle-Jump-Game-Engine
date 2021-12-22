//
// Created by Pablo Deputter on 19/12/2021.
//

#ifndef DOODLEJUMP_SHOPSTATE_H
#define DOODLEJUMP_SHOPSTATE_H

#include "Game.h"

#include "Item.h"
#include "Settings.h"
#include "State.h"
#include "json.hpp"

#include <vector>

using json = nlohmann::json;

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
        std::pair<unsigned int, unsigned int>
            mSelected; /**< std::pair<unsigned int,unsigned int - item selected in row and column */
        std::vector<std::vector<std::shared_ptr<Item>>> mItems; /**< 2D std::vector containing items */
        std::vector<std::shared_ptr<sf::Text>> mInfo;           /**< std::vector containing info text */

        bool mBuying;                          /**< bool - are we in a buying state */
        std::unique_ptr<sf::Text> mBuyingText; /**< sf::Text - text for when we are in a buying state */

        int& mCoins;                          /**< unsigned int - total amount of coins Player has available by ref. */
        std::unique_ptr<sf::Text> mCoinsText; /**< sf::Text - text for coins */
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
         * @brief Select chosen item
         */
        void selectItem();
        /**
         * @brief Move around in menu
         * @param key sf::Keyboard::Key - pressed / released key
         * @param isPressed bool - is key pressed
         */
        void menuMove(sf::Keyboard::Key key, bool isPressed);
        /**
         * @brief Process events
         */
        void processEvents() override;
        /**
         * @brief Get type of State
         * @return GameStates - eShop
         */
        [[nodiscard]] unsigned int getType() const override { return eShop; }

public:
        /**
         * @brief Constructor for ShopState object
         * @param window sf::RenderWindow - pointer to window where state will on draw
         * @param game Game - current game
         * @param items 2D array containing all items
         * @param coins int - total amount of coins Player has available by reference
         */
        ShopState(std::shared_ptr<sf::RenderWindow> window, Game& game,
                  std::vector<std::vector<std::shared_ptr<Item>>> items, int& coins);
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
