//
// Created by Pablo Deputter on 06/12/2021.
//

#include "model/Jetpack.h"
#include "util/Stopwatch.h"

using namespace Model;

void Jetpack::visit(Model::Player& player)
{
        if (mStarted) {
                player.setState(Player::eNormal);
                player.setDrag(0.005f);
                return;
        }
        // Add timer for Jetpack Bonus
        Utils::Stopwatch::getInstance().addTimer(Model::eJetpack, 4.f);
        player.setState(Player::eFlying);
        player.setDrag(0.003f);
        mStarted = true;
}

bool Jetpack::isRemovable() const
{
        // Bonus has started and timer has expired
        if (mStarted && !Utils::Stopwatch::getInstance().checkTimer(Model::eJetpack)) {
                std::shared_ptr<Model::Entity> jetpack = std::make_shared<Model::Jetpack>(true);
                trigger(EventType::STOP_BONUS, std::make_shared<StopBonusEvent>(jetpack));
                return true;
        } else if (mStarted && Utils::Stopwatch::getInstance().checkTimer(Model::eJetpack)) {
                return false;
        }
        return mRemoveFlag;
}