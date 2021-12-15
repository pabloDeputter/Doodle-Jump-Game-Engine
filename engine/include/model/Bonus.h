//
// Created by Pablo Deputter on 16/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_BONUS_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_BONUS_H

#include "Entity.h"

namespace Model {

class Bonus : public Entity
{
protected:
        std::pair<float, float> mBounds;
        bool mMovingDown;
        bool mInit;
        bool mStarted;

private:
        virtual void initBounds();

        void visit(Model::Player& player) override {}

public:
        Bonus(unsigned int score, float spawnRate, bool started)
            : Entity(score), mBounds({0.f, 0.f}), mMovingDown(false), mInit(false), mStarted(started)
        {
        }

        Bonus(unsigned int score, float spawnRate)
            : Entity(score), mBounds({0.f, 0.f}), mMovingDown(false), mInit(false), mStarted(false)
        {
        }

        explicit Bonus(bool started)
            : Entity(), mBounds({0.f, 0.f}), mMovingDown(false), mInit(false), mStarted(started)
        {
        }

        ~Bonus() override = default;
        /**
         * @brief Get type of Entity object
         * @return Model::Type
         */
        [[nodiscard]] Model::Type getType() const override { return Model::Type::eBonus; }

        [[nodiscard]] bool isRemovable() const override {}

        void move(bool collision) override;

        [[nodiscard]] bool isBonus() const override { return true; }
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_BONUS_H
