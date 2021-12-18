//
// Created by Pablo Deputter on 05/12/2021.
//

#ifndef DOODLEJUMP_VERTICALPLATFORM_H
#define DOODLEJUMP_VERTICALPLATFORM_H

#include "Entity.h"

#include "util/Random.h"

/**
 * @brief Namespace holds all Models
 */
namespace Model {
/**
 * @brief Class for Vertical Platform object
 */
class VerticalPlatform : public Entity
{
private:
        std::pair<float, float> mBounds; /**< Move bounds */
        bool mMovingDown;                /**< Is moving downwards */
        float mSpeed;                    /**< Speed when moving */
        bool mInit;                      /**< Are bounds initialized */

private:
        /**
         * @brief Initialize bounds
         */
        void initBounds();
        /**
         * @brief Get type of Vertical Platform
         * @return Model::Type - type of Vertical Platform
         */
        [[nodiscard]] Model::Type getType() const override { return Model::eVertical; }
        /**
         * @brief Move Vertical Platform
         * @param collision bool - collided
         */
        void move(bool collision) override;

public:
        /**
         * @brief Constructor for Horizontal Platform object
         * Standard score of Vertical Platform is 5
         */
        VerticalPlatform() : Entity(7), mBounds({0.f, 0.f}), mInit(false)
        {
                // Generate random float between [0,1] to decide if Platform starts moving down or not
                if (Utils::Random::getInstance().random(0.f, 1.f) >= 0.5f) {
                        mMovingDown = false;
                } else {
                        mMovingDown = true;
                }
                // Generate random velocity
                mSpeed = Utils::Random::getInstance().random(.01f, .025f);
        }
        /**
         * @brief Default destructor for Vertical Platform object
         */
        ~VerticalPlatform() override = default;
};
} // namespace Model

#endif // DOODLEJUMP_VERTICALPLATFORM_H
