//
// Created by Pablo Deputter on 06/12/2021.
//

#ifndef DOODLEJUMP_JETPACK_H
#define DOODLEJUMP_JETPACK_H

#include "Bonus.h"
#include "Player.h"

/**
 * @brief Namespace holds all Models
 */
namespace Model {
/**
 * @brief Class for Jetpack object
 */
class Jetpack : public Bonus
{
private:
        /**
         * @brief Visit Player object to apply Jetpack Bonus
         * @param player Player - Pointer to Player
         */
        void visit(Model::Player& player) override;
        /**
         * @brief Get Type of Jetpack
         * @return Model::Type - type of Jetpack
         */
        [[nodiscard]] Model::Type getType() const override { return Model::eJetpack; }
        /**
         * @brief Check if removable
         * @return bool - true if removable
         */
        [[nodiscard]] bool isRemovable() const override;

public:
        /**
         * @brief Constructor for Jetpack object
         * @param score int - score
         * @param started bool - is Jetpack started
         */
        Jetpack(int score, bool started) : Bonus(score, started) {}
        /**
         * @brief Constructor for Jetpack object
         * Standard score of Jetpack is 25
         */
        Jetpack() : Bonus(25, false) {}
        /**
         * @brief Constructor for Jetpack object
         * @param started bool - is Jetpack started
         */
        explicit Jetpack(bool started) : Bonus(started) {}
        /**
         * @brief Destructor for Jetpack object
         */
        ~Jetpack() override = default;
};
} // namespace Model

#endif // DOODLEJUMP_JETPACK_H
