//
// Created by Pablo Deputter on 16/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_BONUS_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_BONUS_H

#include "Entity.h"

/**
 * @brief Namespace holds all Models
 */
namespace Model {
/**
 * @brief Class for Bonus
 */
class Bonus : public Entity
{
protected:
        std::pair<float, float> mBounds; /**< Move bounds */
        bool mMovingDown;                /**< Is moving down */
        bool mInit;                      /**< Are bounds initialized */
        bool mStarted;                   /**< Is Bonus started */

private:
        /**
         * @brief Initialize bounds
         */
        void initBounds();
        /**
         * @brief Visit Player object to apply Bonus
         * @param player Player - Pointer to Player
         */
        void visit(Model::Player& player) override = 0;
        /**
         * @brief Get type of Bonus
         * @return Model::Type - type of Bonus
         */
        [[nodiscard]] Model::Type getType() const override { return Model::eBonus; }
        /**
         * @brief Move Bonus
         * @param collision bool - collided or not
         */
        void move(bool collision) override;
        /**
         * @brief Check if Bonus is removable
         * @return bool
         */
        [[nodiscard]] bool isRemovable() const override { return mRemoveFlag; }
        /**
         * @brief Check if Entity is Bonus
         * @return bool - true
         */
        [[nodiscard]] bool isBonus() const override { return true; }

public:
        /**
         * @brief Constructor for Bonus object
         * @param score int - score
         * @param started bool - Bonus has started
         */
        Bonus(int score, bool started)
            : Entity(score), mBounds({0.f, 0.f}), mMovingDown(false), mInit(false), mStarted(started)
        {
        }
        /**
         * @brief Constructor for Bonus object
         * @param started bool - Bonus has started
         */
        explicit Bonus(bool started)
            : Entity(), mBounds({0.f, 0.f}), mMovingDown(false), mInit(false), mStarted(started)
        {
        }
        /**
         * @brief Default destructor for Bonus object
         */
        ~Bonus() override = default;
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_BONUS_H
