//
// Created by Pablo Deputter on 13/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H

#include <string>

/**
 * @brief Namespace holds all models
 */
namespace Model {

// enum PlatformType {
//         STATIC = 0,
//         HORIZONTAL = 1,
//         VERTICAL = 2,
//         TEMPORARY = 3
// };

class Entity
{
public:
        virtual std::string getType() const { return ""; }
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ENTITY_H
