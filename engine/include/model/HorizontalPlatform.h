//
// Created by Pablo Deputter on 05/12/2021.
//

#ifndef DOODLEJUMP_HORIZONTALPLATFORM_H
#define DOODLEJUMP_HORIZONTALPLATFORM_H

#include "Entity.h"

#include "util/Random.h"

/**
 * @brief Namespace holds all Models
 */
namespace Model {
/**
 * @brief Class for Horizontal Platform object
 */
class HorizontalPlatform : public Entity
{
private:
        std::pair<float, float> mBounds; /**< Move bounds */
        bool mMovingForward;             /**< Is moving forward */
        float mSpeed;                    /**< Speed when moving */
        bool mInit;                      /**< Are bounds initialized */

private:
        /**
         * @brief Initialize bounds
         */
        void initBounds();

public:
        /**
         * @brief Constructor for Horizontal Platform object
         * Standard score of Horizontal Platform is 5
         */
        HorizontalPlatform() : Entity(5), mBounds({0.f, 0.f}), mInit(false)
        {
                // Generate random float between [0,1] to decide if Platform starts moving forward or not
                if (Utils::Random::getInstance().random(0.f, 1.f) >= 0.5f) {
                        mMovingForward = false;
                } else {
                        mMovingForward = true;
                }
                // Generate random velocity
                mSpeed = Utils::Random::getInstance().random(.02f, .05f);
        }
        /**
         * @brief Default destructor for Horizontal Platform object
         */
        ~HorizontalPlatform() override = default;
        /**
         * @brief Get type of Horizontal Platform
         * @return Model::Type - type of Horizontal Platform
         */
        [[nodiscard]] Model::Type getType() const override { return Model::eHorizontal; }
        /**
         * @brief Move Horizontal Platform
         * @param collision bool - collided
         */
        void move(bool collision) override;
};
} // namespace Model

#endif // DOODLEJUMP_HORIZONTALPLATFORM_H
