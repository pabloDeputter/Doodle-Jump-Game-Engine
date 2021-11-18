//
// Created by Pablo Deputter on 15/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_TRANSFORM_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_TRANSFORM_H

#include <utility>

namespace Utils {

class Transform
{
private:
        float mWindowWidth;
        float mWindowHeight;

        Transform() = default;

        static Transform& Get();

        void ISetDimensions(float width, float height);

        std::pair<float, float> IGetDimensions() const;

public:
        Transform(const Transform&) = delete;

        Transform& operator=(const Transform&) = delete;

        static void SetDimensions(float width, float height);

        static std::pair<float, float> GetDimensions();
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_TRANSFORM_H
