//
// Created by Pablo Deputter on 06/12/2021.
//

#include "model/Jetpack.h"

#include "util/Camera.h"
#include "util/Stopwatch.h"

using namespace Model;

void Jetpack::visit(Model::Player& player)
{
        // If Jetpack power-up has already started, we need to disable it
        if (mStarted) {
                // Set state of Player back to normal
                player.setState(Player::eNormal);
                player.setDrag(0.005f);
                // Clear registered observers from Jetpack
                clear();
                return;
        }
        // Add countdown timer for Jetpack Bonus
        Utils::Stopwatch::getInstance().addTimer(Model::eJetpack, 3.2f);
        // Set state of Player to flying and decrease drag
        player.setState(Player::eFlying);
        player.setDrag(0.003f);
        mStarted = true;
        // Move out of world to avoid further collisions
        setX(Utils::Camera::getInstance().getWorldDimensions().first * 2.f);
        // Jetpack can be removed next time active Entities are cleared, but beware that the
        // countdown also needs to be expired.
        setRemoveFlag(true);
}

bool Jetpack::isRemovable() const
{
        // Bonus has started and timer has expired we can disable power-up and return true
        if (mStarted && !Utils::Stopwatch::getInstance().checkTimer(Model::eJetpack)) {
                std::shared_ptr<Model::Entity> jetpack = std::make_shared<Model::Jetpack>(true);
                trigger(EventType::STOP_BONUS, std::make_shared<StopBonusEvent>(jetpack));
                return true;
        }
        // If timer is yet to expire we return false
        else if (mStarted && Utils::Stopwatch::getInstance().checkTimer(Model::eJetpack)) {
                return false;
        }
        // By default return mRemoveFlag
        return mRemoveFlag;
}