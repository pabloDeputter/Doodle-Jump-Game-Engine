//
// Created by Pablo Deputter on 16/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_BONUS_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_BONUS_H

#include "Entity.h"

namespace Model {

class Bonus : public Entity
{
public:
        /**
         * @brief Enum containing enumerated Bonuses
         */
        enum Sort
        {
                eJetpack = 0,
                eSpring = 1,
        };

private:
        Bonus::Sort mSort;

public:
        /**
         * @brief Get type of Entity object
         * @return Model::Type
         */
        Model::Type getType() const override { return Model::Type::eBonus; }
        /**
         * @brief Get sort of Bonus object
         * @return
         */
        Sort getMSort() const;
        /**
         * @brief Set sort of Bonus object
         * @param sort Bonus::Sort
         */
        void setMSort(Sort sort);
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_BONUS_H
