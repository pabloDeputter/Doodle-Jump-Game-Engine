//
// Created by Pablo Deputter on 13/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H

#include <string>

#include "../Observer/Observable.h"

/**
 * @brief Namespace holds all models
 */
namespace Model {

///**
// * @Brief Namespace contains all different entities
// */
enum Type
{
        ePlayer = 0,
        eJetpack = 1,
        eSpring = 2,
        ePlatform = 3,
};

class Entity : public Observer::Observable
{
public:
        // Pure virtual
        virtual Model::Type getType() const = 0;
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
