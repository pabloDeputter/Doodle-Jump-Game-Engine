//
// Created by Pablo Deputter on 07/12/2021.
//

#ifndef DOODLEJUMP_IVISITOR_H
#define DOODLEJUMP_IVISITOR_H

#include <memory>

namespace Model {
class Player;
}

/*
 * @brief Namespace hold Visitor pattern
 */
namespace Visitor {
/**
 * @brief Class for abstract Visitor
 */
class IVisitor
{
public:
        /**
         * @brief Visit Player object to apply Bonus
         * @param player Player - Pointer to Player
         */
        virtual void visit(Model::Player& player) = 0;
};
} // namespace Visitor

#endif // DOODLEJUMP_IVISITOR_H
