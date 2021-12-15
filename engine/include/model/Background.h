//
// Created by Pablo Deputter on 29/11/2021.
//

#ifndef DOODLEJUMP_BACKGROUND_H
#define DOODLEJUMP_BACKGROUND_H

#include "Entity.h"

/**
 * @brief Namespace holds all Models
 */
namespace Model {
/**
 * @brief Class for Background tile
 */
class Background : public Entity
{
public:
        /**
         * @brief Default constructor for Background object
         */
        Background() = default;
        /**
         * @brief Default destructor for Background object
         */
        ~Background() override = default;
        /**
         * @brief Get type of Background
         * @return Model::Type - type of Background
         */
        [[nodiscard]] Model::Type getType() const override { return Model::eBackground; }
        /**
         * @brief Move Background
         * @param collision bool - collided or not
         */
        void move(bool collision) override {}
};
} // namespace Model

#endif // DOODLEJUMP_BACKGROUND_H
