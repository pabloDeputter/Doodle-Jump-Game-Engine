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
        std::vector<sf::Text> mSettings;
        unsigned int mSelected;

private:
        /**
         * @brief Render state
         */
        void render() const override
        {
                mWindow->clear(sf::Color::Black);
                for (const auto& i : mSettings) {
                        mWindow->draw(i);
                }
                mWindow->display();
        }
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
