//
// Created by Pablo Deputter on 05/12/2021.
//

#ifndef DOODLEJUMP_STATICPLATFORM_H
#define DOODLEJUMP_STATICPLATFORM_H

#include "Entity.h"

/**
 * @brief Namespace holds all Models
 */
namespace Model {
/**
 * @brief Class for Static Platform object
 */
class StaticPlatform : public Entity
{
public:
        /**
         * @brief Constructor for Static Platform object
         * Standard score of Static Platform is 2
         */
        StaticPlatform() : Entity(2) {}
        /**
         * @brief Default destructor for Static Platform object
         */
        ~StaticPlatform() override = default;

private:
        /**
         * @brief Get type of Static Platform
         * @return Model::Type - type of Static Platform
         */
        [[nodiscard]] Model::Type getType() const override { return Model::eStatic; }
        /**
         * @brief Move Static Platform
         * @param collision bool - collided
         */
        void move(bool collision) override {}
};
} // namespace Model

#endif // DOODLEJUMP_STATICPLATFORM_H
