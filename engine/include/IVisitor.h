//
// Created by Pablo Deputter on 07/12/2021.
//

#ifndef DOODLEJUMP_IVISITOR_H
#define DOODLEJUMP_IVISITOR_H

#include <memory>

namespace Model {
class Player;
}

namespace Visitor {

class IVisitor
{
public:
        virtual void visit(Model::Player& player) = 0;
};
} // namespace Visitor

#endif // DOODLEJUMP_IVISITOR_H
