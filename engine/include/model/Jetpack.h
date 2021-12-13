//
// Created by Pablo Deputter on 06/12/2021.
//

#ifndef DOODLEJUMP_JETPACK_H
#define DOODLEJUMP_JETPACK_H

#include "Player.h"

namespace Model {

class Jetpack : public Entity
{
private:
        std::pair<float, float> mBounds;
        bool mMovingDown;
        bool mInit;

public:
        bool mStarted;

public:
        Jetpack(bool started) : Entity(20, .25f), mMovingDown(false), mInit(false), mStarted(started) {}

        ~Jetpack() override = default;

        [[nodiscard]] Model::Type getType() const override;

        void move(bool collision) override;

        void initBounds();

        // TODO - jetpack
        void visit(Model::Player& player) override
        {
                std::cout << "visit\n";
                if (mStarted) {
                        std::cout << "return player state\n";
                        player.setDrag(0.006f);
                        return;
                }
                Utils::Stopwatch::getInstance().addTimer(Model::eJetpack, 2.5f);
                player.setDrag(0.f);
                mStarted = true;
        }
        // TODO - observer pattern mss
        // event met player dus dan kan die accepten als gedaan is
        bool isRemovable() const override
        {
                // moet removeflag en gestart zijn en de timer moet afgelopen zijn
                if (mStarted && mStarted && Utils::Stopwatch::getInstance().checkTimer(Model::eJetpack)) {
                        std::shared_ptr<Model::Entity> jetpack = std::make_shared<Model::Jetpack>(true);

                        trigger(EventType::STOP_BONUS, std::make_shared<StopBonusEvent>(jetpack));
                        std::cout << "jetpackStopped\n";
                        return true;
                }
                return false;
        }

        bool isBonus() const override { return true; }
};
} // namespace Model

#endif // DOODLEJUMP_JETPACK_H
