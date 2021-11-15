//
// Created by Pablo Deputter on 15/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_TRANSFORM_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_TRANSFORM_H

namespace Utils {

class Transform
{
private:
        int mWindowWidth;
        int mWindowHeight;

        Transform() = default;

        static Transform& Get();

        void ISetDimensions(int width, int height);

public:
        Transform(const Transform&) = delete;

        Transform& operator=(const Transform&) = delete;

        static void SetDimensions(int width, int height);
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_TRANSFORM_H
