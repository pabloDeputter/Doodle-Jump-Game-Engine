//
// Created by Pablo Deputter on 14/12/2021.
//

#ifndef DOODLEJUMP_MENUSTATE_H
#define DOODLEJUMP_MENUSTATE_H

#include "util/ResourceManager.h"
#include "util/Utilities.h"

#include "Game.h"
#include "HighScore.h"
#include "State.h"

#include <utility>

// TODO
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
        sf::Text mTitle;
        sf::Text mScores;
        sf::Text mHighScore;
        sf::Text mInfo;

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
        void handleInput(sf::Keyboard::Key key, bool isPressed) const;
        /**
         * @brief Process events
         */
        void processEvents() override;
        /**
         * @brief Get type of State
         * @return GameStates - eMenu
         */
        [[nodiscard]] unsigned int getType() const override { return eMenu; }

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
        ~MenuState() override = default;
};
} // namespace States

#endif // DOODLEJUMP_MENUSTATE_H
