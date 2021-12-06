//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_CAMERA_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_CAMERA_H

#include "Observer.h"

#include <utility>

/**
 * @brief Namespace holds all Utilities
 */
namespace Utils {
/**
 * @brief Class for Camera
 */
class Camera
{
private:
        float mWorldLeft;   /**< Leftmost x-coordinate of world */
        float mWorldRight;  /**< Rightmost x-coordinate of world */
        float mWorldTop;    /**< Topmost x-coordinate of world */
        float mWorldBottom; /**< Bottommost x-coordinate of world */

        float mWindowLeft;   /**< Leftmost x-coordinate of window */
        float mWindowRight;  /**< Rightmost x-coordinate of window */
        float mWindowTop;    /**< Topmost y-coordinate of window */
        float mWindowBottom; /**< Bottommost y-coordinate of window */

        float mCameraX; /**< X-coordinate of Camera */
        float mCameraY; /**< Y-coordinate of Camera */

        float mMaxHeight; /**< Max height Player has jumped */

        /**
         * @brief Private default constructor
         */
        Camera() = default;

public:
        /**
         * @brief Default destructor
         */
        virtual ~Camera() = default;
        /**
         * @brief Deleted copy constructor
         */
        Camera(const Camera&) = delete;
        /**
         * @brief Deleted assignment operator
         * @return Camera
         */
        Camera& operator=(const Camera&) = delete;
        /**
         * @brief Get instance of Camera object
         * @return Camera
         */
        static Camera& getInstance();
        /**
         * @brief Get world dimensions
         * @return std::pair<float, float>
         */
        [[nodiscard]] std::pair<float, float> getWorldDimensions() const;
        /**
         * @brief Set world dimensions
         * @param right float
         * @param top float
         * @param left float
         * @param bottom float
         */
        void setWorldDimensions(float right, float top, float left = 0, float bottom = 0);
        /**
         * @brief Get window dimensions
         * @return
         */
        [[nodiscard]] std::pair<float, float> getWindowDimensions() const;
        /**
         * @brief Set viewport / window dimensions
         * @param right float
         * @param bottom float
         * @param left float
         * @param top float
         */
        void setWindowDimensions(float right, float bottom, float left = 0, float top = 0);

        /**
         * @brief Transforms world coordinates to viewport / window coordinates
         * @param x float
         * @param y float
         * @return std::pair<float, float>
         */
        [[nodiscard]] std::pair<float, float> transform(float x, float y) const;
        /**
         * @brief Transforms viewport / window coordinates to world coordinates
         * @param x float
         * @param y float
         * @return std::pair<float, float>
         */
        [[nodiscard]] std::pair<float, float> inverseTransform(float x, float y) const;
        /**
         * @brief Move Camera
         * @param x float
         * @param y float
         */
        void move(float x, float y);
        /**
         * @brief Get x coordinate of Camera
         * @return float
         */
        [[nodiscard]] float getX() const;
        /**
         * @brief Get y coordinate of Camera
         * @return float
         */
        [[nodiscard]] float getY() const;
        /**
         * @brief Get maximum height of Camera
         * @return float
         */
        [[nodiscard]] float getMaxHeight() const;
        /**
         * @brief Check if given height is greater or equal to current maximum height
         * @param height float
         * @return bool
         */
        bool isMaxHeight(float height);
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_CAMERA_H
