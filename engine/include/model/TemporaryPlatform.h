//
// Created by Pablo Deputter on 05/12/2021.
//

#ifndef DOODLEJUMP_TEMPORARYPLATFORM_H
#define DOODLEJUMP_TEMPORARYPLATFORM_H

#include "Entity.h"

/**
 * @brief Namespace holds all Models
 */
namespace Model {
/**
 * @brief Class for Temporary Platform object
 */
class TemporaryPlatform : public Entity
{
public:
        /**
         * @brief Constructor for Temporary Platform object
         * Standard score of Temporary Platform is 10
         */
        TemporaryPlatform() : Entity(10) {}
        /**
         * @brief Default destructor for Temporary Platform object
         */
        ~TemporaryPlatform() override = default;

private:
        /**
         * @brief Get type of Temporary Platform
         * @return Model::Type - type of Temporary Platform
         */
        [[nodiscard]] Model::Type getType() const override { return Model::eTemporary; }
        /**
         * @brief Move Temporary Platform
         * @param collision bool - collided
         */
        void move(bool collision) override
        {
                // If collided, Temporary Platform can be destroyed
                if (collision) {
                        Entity::setRemoveFlag(true);
                        Observer::Subject::clear();
                }
        }
};
} // namespace Model

#endif // DOODLEJUMP_TEMPORARYPLATFORM_H
