//
// Created by Pablo Deputter on 19/12/2021.
//

#ifndef DOODLEJUMP_COIN_H
#define DOODLEJUMP_COIN_H

#include "Bonus.h"
#include "Player.h"

#include <cmath>

/**
 * @brief Namespace holds all Models
 */
namespace Model {
/**
 * @brief Class for Coin object
 */
class Coin : public Bonus
{
private:
        /**
         * @brief Visit Player object to apply Coin Bonus
         * @param player Player - Pointer to Player
         */
        void visit(Model::Player& player) override
        {
                // Move out of world to avoid further collisions
                setX(Utils::Camera::getInstance().getWorldDimensions().first * 2.f);
                // Coin can be removed next time active Entities are cleared
                setRemoveFlag(true);
                mStarted = true;
        }
        /**
         * @brief Get Type of Coin
         * @return Model::Type - type of Coin
         */
        [[nodiscard]] Model::Type getType() const override { return Model::eCoin; }

public:
        /**
         * @brief Constructor for Coin object
         * @param score int - score
         * @param started bool - is Coin started
         */
        Coin(int score, bool started) : Bonus(score, started){};
        /**
         * @brief Constructor for Coin object
         * Standard score of Spring is 15
         */
        Coin() : Bonus(20, false){};
        /**
         * @brief Destructor for Coin object
         */
        ~Coin() override = default;
};
} // namespace Model

#endif // DOODLEJUMP_COIN_H
