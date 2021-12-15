//
// Created by Pablo Deputter on 14/12/2021.
//

#ifndef DOODLEJUMP_PLAYSTATE_H
#define DOODLEJUMP_PLAYSTATE_H

#include "World.h"

#include "Game.h"

#include "MenuState.h"
#include "State.h"

#include <utility>

/**
 * @brief Namespace holds States
 */
namespace States {
/**
 * @brief Class for when Game is playing
 */
class PlayState : public State
{
private:
        std::unique_ptr<World> mWorld; /**< Pointer to game World */
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
         * @return GameStates - ePlay
         */
        [[nodiscard]] unsigned int getType() const override { return ePlay; }

public:
        /**
         * @brief Constructor for GameState object
         * @param world World - Pointer to game World
         * @param window sf::RenderWindow - pointer to window where state will on draw
         * @param game Game - current game
         */
        PlayState(std::unique_ptr<World> world, std::shared_ptr<sf::RenderWindow> window, Game& game);
        /**
         * @brief Destructor for GameState object
         */
        ~PlayState() override { mWorld->destroy(); }
};
} // namespace States

#endif // DOODLEJUMP_PLAYSTATE_H
