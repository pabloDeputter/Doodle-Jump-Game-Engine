//
// Created by Pablo Deputter on 13/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORM_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORM_H

#include "Entity.h"

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

public:
        /**
         * @brief Get type of Entity object
         * @return Model::Type
         */
        Model::Type getType() const override { return Model::Type::ePlatform; }
        /**
         * @brief Get sort of Platform object
         * @return
         */
        Sort getMSort() const;
        /**
         * @brief Set sort of Platform object
         * @param sort Bonus::Sort
         */
        void setMSort(Sort sort);
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORM_H
