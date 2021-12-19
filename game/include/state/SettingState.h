//
// Created by Pablo Deputter on 18/12/2021.
//

#ifndef DOODLEJUMP_SETTINGSTATE_H
#define DOODLEJUMP_SETTINGSTATE_H

#include "Game.h"

#include "Settings.h"
#include "State.h"

#include <vector>

/**
 * @brief Namespace holds States
 */
namespace States {
/**
 * @brief Class for when in Settings
 */
class SettingState : public State
{
private:
        std::vector<std::shared_ptr<sf::Text>> mSettings; /**< std::vector containing all different difficulties */
        unsigned int mSelected;                           /**< unsigned int - selected setting */
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
         * @return GameStates - eSettings
         */
        [[nodiscard]] unsigned int getType() const override { return eSettings; }

public:
        /**
         * @brief Constructor for SettingState object
         * @param window sf::RenderWindow - pointer to window where state will on draw
         * @param game Game - current game
         * @param diff Settings::Difficulty - currently selected difficulty
         */
        SettingState(std::shared_ptr<sf::RenderWindow> window, Game& game, Settings::Difficulty diff);
        /**
         * @brief Destructor for SettingState object
         */
        ~SettingState() override { mSettings.clear(); }
};
} // namespace States

#endif // DOODLEJUMP_SETTINGSTATE_H
