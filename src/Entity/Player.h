//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYER_H

#include "Entity.h"

namespace Model {

class Player : public Entity
{
private:
        std::pair<float, float> mVelocity;  /**< Current velocity of Player */
        std::pair<float, float> mDirection; /**< Current direction of Player */
        const float maxVelocity = 27.f;     /**< Max velocity Player can achieve */
        const float acceleration = 1.5;     /**< Acceleration of Player */
        const float drag = 0.6f;            /**< Resistance applied to Player */

public:
        Model::Type getType() const override { return Model::Type::ePlayer; }
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYER_H
