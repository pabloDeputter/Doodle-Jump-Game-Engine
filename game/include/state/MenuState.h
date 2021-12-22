//
// Created by Pablo Deputter on 14/12/2021.
//

#ifndef DOODLEJUMP_MENUSTATE_H
#define DOODLEJUMP_MENUSTATE_H

#include "Settings.h"
#include "util/ResourceManager.h"
#include "util/Utilities.h"

#include "Game.h"
#include "HighScore.h"
#include "Item.h"
#include "State.h"

#include "json.hpp"

#include <memory>
#include <ostream>
#include <utility>
#include <vector>

using json = nlohmann::json;

/**
 * @brief Namespace holds all States
 */
namespace States {
/**
 * @brief Class for when Player is in Menu and can watch the high scores
 */
class MenuState : public State
{
private:
        std::unique_ptr<sf::Sprite> mTitle; /**< sf::Sprite - Title logo */
        std::vector<std::unique_ptr<sf::Text>>
            mScores; /**< std::vector<sf::Text> - std::vector containing high scores */

        std::vector<std::shared_ptr<sf::Text>> mInfo; /**< std::vector<sf::Text> - std::vector containing info */
        unsigned int mSelected;                       /**< unsigned int - index of selected info */

        unsigned int mIndex; /**< unsigned int - index of new high score that was achieved */
        bool mEnterName;     /**< bool - true if we are entering a name */
        std::string mName;   /**< std::string - entered name of new high score that was achieved */

        unsigned int mDiff; /**< unsigned int - selected difficulty */

        std::unique_ptr<sf::Text> mCoinsText; /**< sf::Text - text for coins */
        int mCoins;                           /**< int - total coins collected */

        std::string mPath; /**< std::string - path to config file */

        std::unique_ptr<sf::Sound> mSound;                      /**< sf::Sound - menu sound */
        std::vector<std::vector<std::shared_ptr<Item>>> mItems; /**< 2D array containing items */
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
         * @return GameStates - eMenu
         */
        [[nodiscard]] unsigned int getType() const override { return eMenu; }
        /**
         * @brief Create / initialize scores text
         */
        void createScores();
        /**
         * @brief Update score name when entering std::string for new high score
         */
        void updateScoreName();
        /**
         * @brief Update info, highlight selected info
         */
        void updateInfo();
        /**
         * @brief Gets triggered when user presses enter after selecting one of the info actions
         */
        void onSelect();
        /**
         * @brief Gets called when a new high score is achieved
         */
        void newHighScore(int coins) override;
        /**
         * @brief Set new difficulty
         * @param diff unsigned int - new difficulty
         */
        void setNewDiff(unsigned int diff) override { mDiff = diff; }
        /**
         * @brief Save coins, high scores, items, ... to json
         * @param j json - json containing highs cores
         */
        void save(json& j) const;

public:
        /**
         * @brief Constructor for MenuState object
         * @param window sf::RenderWindow - pointer to window where state will on draw
         * @param game Game - current game
         */
        MenuState(std::shared_ptr<sf::RenderWindow> window, Game& game);
        /**
         * @brief Destructor for MenuState object
         */
        ~MenuState() override
        {
                json j = HighScore::getInstance().save();
                save(j);
                mScores.clear();
                mInfo.clear();
        }
};
} // namespace States

#endif // DOODLEJUMP_MENUSTATE_H
