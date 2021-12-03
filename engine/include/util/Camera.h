//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_CAMERA_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_CAMERA_H

#include "Observer.h"

#include <utility>

// TODO - check if correct
// TODO - observer pattern
// TODO - struct...
namespace Utils {

class Camera
{
private:
        float mGameLeft;   /**< Leftmost x-coordinate of window */
        float mGameRight;  /**< Rightmost x-coordinate of window */
        float mGameTop;    /**< Topmost x-coordinate of window */
        float mGameBottom; /**< Bottommost x-coordinate of window */

        float mWindowLeft;   /**< Leftmost x-coordinate of window */
        float mWindowRight;  /**< Rightmost x-coordinate of window */
        float mWindowTop;    /**< Topmost y-coordinate of window */
        float mWindowBottom; /**< Bottommost y-coordinate of window */

        float mCameraX; /**< X-coordinate of Camera */
        float mCameraY; /**< Y-coordinate of Camera */

        float mMaxHeight; /**< Max height Player has jumped */

        // TODO - currently unused
        float mCenterX; /** Center of Camera */
        float mCenterY; /** Center of Camera */

        float mCameraWidth;  /**< Width of Game / Camera area */
        float mCameraHeight; /**< Height of Game / Camera area */

        Camera() = default;

public:
        //        ~Camera() override = default;

        ~Camera() = default;

        Camera(const Camera&) = delete;

        Camera& operator=(const Camera&) = delete;

        static Camera& getInstance();
        /**
         * @brief Set viewport / window dimensions
         * @param right float
         * @param bottom float
         * @param left float
         * @param top float
         */
        void setWindowDimensions(float right, float bottom, float left = 0, float top = 0);
        /**
         * @brief Set game dimensions
         * @param right float
         * @param top float
         * @param left float
         * @param bottom float
         */
        void setGameDimensions(float right, float top, float left = 0, float bottom = 0);
        /**
         * @brief Transform world coordinates to viewport / window coordinates
         * @param x float - x coordinate
         * @param y float - y coordinate
         * @return std::pair<float, float> - transformed coordinates
         */
        std::pair<float, float> transform(float x, float y) const;

        std::pair<float, float> inverseTransform(float x, float y) const;

        void move(float x, float y)
        {
                mCameraX = x;
                mCameraY = y;
        }

        //        /**
        //         * @brief Get Camera position
        //         * @return std::pair<float, float> - Camera coordinates
        //         */
        //        std::pair<float, float> getPosition() const;

        float getX() const;

        float getY() const;

        std::pair<float, float> getWindowDimensions() const;

        std::pair<float, float> getGameDimensions() const;

        float getMaxHeight() const;

        bool isMaxHeight(float height);
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_CAMERA_H
