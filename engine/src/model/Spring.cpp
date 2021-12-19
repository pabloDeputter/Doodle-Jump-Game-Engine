//
// Created by Pablo Deputter on 06/12/2021.
//

#include "model/Spring.h"

using namespace Model;

void Spring::visit(Player& player)
{
        // Original jump Player can achieve with default velocity
        float jumpPeak = (player.getMaxVelocity() / player.getDrag()) * (player.getMaxVelocity() / 2.f);
        // Calculate speed needed for a jump with a vertical distance x5
        float newSpeed = sqrt((jumpPeak * 5) * (player.getDrag() * 2.f));
        // Set new velocity of Player
        player.setVelocity({player.getVelocity().first, newSpeed});
        // Move out of world to avoid further collisions
        setX(Utils::Camera::getInstance().getWorldDimensions().first * 2.f);
        // Spring can be removed next time active Entities are cleared
        setRemoveFlag(true);
        mStarted = true;
}