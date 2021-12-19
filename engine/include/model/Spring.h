//
// Created by Pablo Deputter on 06/12/2021.
//

#ifndef DOODLEJUMP_SPRING_H
#define DOODLEJUMP_SPRING_H

#include "Bonus.h"
#include "Player.h"

#include <cmath>

/**
 * @brief Namespace holds all Models
 */
namespace Model {
/**
 * @brief Class for Spring object
 */
class Spring : public Bonus
{
private:
        /**
         * @brief Visit Player object to apply Spring Bonus
         * @param player Player - Pointer to Player
         */
        void visit(Model::Player& player) override;
        /**
         * @brief Get Type of Jetpack
         * @return Model::Type - type of Jetpack
         */
        [[nodiscard]] Model::Type getType() const override { return Model::eSpring; }

public:
        /**
         * @brief Constructor for Spring object
         * @param score int - score
         * @param started bool - is Spring started
         */
        Spring(int score, bool started) : Bonus(score, started){};
        /**
         * @brief Constructor for Spring object
         * Standard score of Spring is 15
         */
        Spring() : Bonus(15, false){};
        /**
         * @brief Destructor for Spring object
         */
        ~Spring() override = default;
};
} // namespace Model

#endif // DOODLEJUMP_SPRING_H
