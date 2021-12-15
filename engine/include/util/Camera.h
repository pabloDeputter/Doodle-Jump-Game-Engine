//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_CAMERA_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_CAMERA_H

#include "observer/Subject.h"

#include <memory>
#include <utility>

/**
 * @brief Namespace holds all Utilities
 */
namespace Utils {
/**
 * @brief Class for Camera implemented using singleton pattern
 */
class Camera : public Observer::Subject
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

        float mLastMaxHeight; /**< Last max height */
        float mMaxHeight;     /**< Max height Player has jumped */

        /**
         * @brief Constructor for Camera object
         */
        Camera()
            : mWorldLeft(0.f), mWorldRight(0.f), mWorldTop(0.f), mWorldBottom(0.f), mWindowLeft(0.f), mWindowRight(0.f),
              mWindowTop(0.f), mWindowBottom(0.f), mCameraX(0.f), mCameraY(0.f), mLastMaxHeight(0.f), mMaxHeight(0.f)
        {
        }

public:
        /**
         * @brief Destructor for Camera object
         */
        ~Camera() override { Observer::Subject::clear(); }
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
         * @brief Reset Camera
         */
        void reset();
        /**
         * @brief Get world dimensions
         * @return std::pair<float,float> - world dimensions
         */
        [[nodiscard]] std::pair<float, float> getWorldDimensions() const { return {mWorldRight, mWorldTop}; }
        /**
         * @brief Set world dimensions
         * @param right float
         * @param top float
         * @param left float
         * @param bottom float
         */
        void setWorldDimensions(float right, float top, float left = 0.f, float bottom = 0.f);
        /**
         * @brief Get window dimensions
         * @return std::pair<float,float> - window dimensions
         */
        [[nodiscard]] std::pair<float, float> getWindowDimensions() const { return {mWindowRight, mWindowBottom}; }
        /**
         * @brief Set viewport / window dimensions
         * @param right float
         * @param bottom float
         * @param left float
         * @param top float
         */
        void setWindowDimensions(float right, float bottom, float left = 0.f, float top = 0.f);
        /**
         * @brief Transforms world coordinates to viewport / window coordinates
         * @param x float
         * @param y float
         * @return std::pair<float,float> - transformed window coordinates
         */
        [[nodiscard]] std::pair<float, float> transform(float x, float y, float left = 0.f, float top = 0.f) const;
        /**
         * @brief Transforms viewport / window coordinates to world coordinates
         * @param x float
         * @param y float
         * @return std::pair<float,float> - transformed world coordinates
         */
        [[nodiscard]] std::pair<float, float> inverseTransform(float x, float y) const;
        /**
         * @brief Move Camera
         * @param x float - x value to be added to mCameraX
         * @param y float - y value to be added to mCameraY
         */
        void move(float x, float y);
        /**
         * @brief Get x coordinate of Camera
         * @return float - x coordinate
         */
        [[maybe_unused]] [[nodiscard]] float getX() const { return mCameraX; }
        /**
         * @brief Get y coordinate of Camera
         * @return float - y coordinate
         */
        [[nodiscard]] float getY() const { return mCameraY; }
        /**
         * @brief Get maximum height of Camera
         * @return float - max. height
         */
        [[nodiscard]] float getMaxHeight() const { return mMaxHeight; }
        /**
         * @brief Get last maximum height of Camera
         * @return float - last max. height
         */
        [[maybe_unused]] [[nodiscard]] float getLastMaxHeight() const { return mLastMaxHeight; }
        /**
         * @brief Check if given height is greater or equal to current maximum height
         * @param height float
         * @return bool
         */
        bool isMaxHeight(float height);
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_CAMERA_H
