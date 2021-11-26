//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_CAMERA_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_CAMERA_H

#include <utility>

class Camera
{
public:
        float mViewportWidth;  /**< Width of Window area */
        float mViewportHeight; /**< Height of Window area */

        float mCameraWidth;  /**< Width of Game / Camera area */
        float mCameraHeight; /**< Height of Game / Camera area */

        float mCameraX; /**< X-coordinate of Camera */
        float mCameraY; /**< Y-coordinate of Camera */

        float mOffsetMaxX;
        float mOffsetMinX;
        float mOffsetMaxY;
        float mOffsetMinY;

public:
        Camera() = default;

        ~Camera() = default;

        void setViewportDimensions(float width, float height);

        std::pair<float, float> getViewPortDimensions() const;

        void setCameraDimensions(float width, float height);

        std::pair<float, float> getCameraDimensions() const;
};

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_CAMERA_H
