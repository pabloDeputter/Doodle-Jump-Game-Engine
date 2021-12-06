//
// Created by Pablo Deputter on 06/12/2021.
//

#ifndef DOODLEJUMP_SPRING_H
#define DOODLEJUMP_SPRING_H

#include "Entity.h"

namespace Model {

class Spring : public Entity
{
public:
        Spring() = default;

        ~Spring() override = default;

        [[nodiscard]] Model::Type getType() const override;

        void move(bool collision) override;
};
} // namespace Model

#endif // DOODLEJUMP_SPRING_H
