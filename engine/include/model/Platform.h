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
public:
        enum Sort
        {
                eStatic = 0,
                eHorizontal = 1,
                eVertical = 2,
                eTemporary = 3
        };

private:
        Platform::Sort mSort;

        std::pair<float, float> mBoundX = {0.f, 0.f};
        bool mMovingForward = true;

        std::pair<float, float> mBoundY = {0.f, 0.f};
        bool mMovingDown = true;

public:
        Platform()
        {
                float rand = Utils::Random::GetRandom(0.f, 1.f);
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
        Model::Type getType() const override { return Model::Type::ePlatform; }

        void move(bool collision) override;

        void initBounds();

        /**
         * @brief Get sort of Platform object
         * @return
         */
        Sort getSort() const;
        /**
         * @brief Set sort of Platform object
         * @param sort Bonus::Sort
         */
        void setSort(Sort sort);
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORM_H
