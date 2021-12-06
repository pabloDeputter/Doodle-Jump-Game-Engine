//
// Created by Pablo Deputter on 13/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORM_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORM_H

#include "Entity.h"
#include "util/Random.h"
#include <iostream>

namespace Model {

class Platform : public Entity
{
private:
        Model::Type mSort;

        std::pair<float, float> mBoundX = {0.f, 0.f};
        bool mMovingForward = true;

        std::pair<float, float> mBoundY = {0.f, 0.f};
        bool mMovingDown = true;

public:
        explicit Platform(Model::Type sort) : mSort(sort) {}

        Platform()
        {
                float rand = Utils::Random::getInstance().random(0.f, 1.f);
                // TODO - remove
                //                std::cout << rand << std::endl;
                if (rand <= .75f)
                        mSort = eStatic;
                else if (.85f >= rand >= .75f)
                        mSort = eHorizontal;
                else if (.95f >= rand >= .85f)
                        mSort = eVertical;
                else
                        mSort = eTemporary;
        }

        ~Platform() override = default;

        /**
         * @brief Get type of Entity object
         * @return Model::Type
         */
        Model::Type getType() const override { return mSort; }

        void move(bool collision) override;

        void initBounds();
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORM_H
