//
// Created by Pablo Deputter on 14/12/2021.
//

#ifndef DOODLEJUMP_ENTERSCORESTATE_H
#define DOODLEJUMP_ENTERSCORESTATE_H

#include "Game.h"
#include "HighScore.h"
#include "State.h"

#include <utility>

/**
 * @brief Namespace holds all States
 */
namespace States {
/**
 * @brief Class for when user is asked to enter name
 */
class EnterScoreState : public State
{
private:
        sf::Text mTitle;         /**< Title */
        sf::Text mInfo;          /**< Info */
        sf::Text mName;          /**< Name of player who achieved new high score */
        std::string mStringName; /**< Entered name */
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
         * @brief Process events
         */
        void processEvents() override;
        /**
         * @brief Get type of State
         * @return GameStates - eEnterScore
         */
        unsigned int getType() const override { return eEnterScore; }

public:
        /**
         * @brief Constructor for EnterScoreState object
         * @param window sf::RenderWindow - pointer to window where state will on draw
         * @param game Game - current game
         */
        EnterScoreState(std::shared_ptr<sf::RenderWindow> window, Game& game);
        /**
         * @brief Destructor for EnterScoreState object
         */
        ~EnterScoreState() override = default;
};
} // namespace States
#endif // DOODLEJUMP_ENTERSCORESTATE_H
