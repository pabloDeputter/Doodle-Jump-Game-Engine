//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_OBSERVER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_OBSERVER_H

#include <memory>

/**
 * @brief Namespace holds Observer pattern
 */
namespace Observer {
/**
 * @brief Class for Observer of Observer pattern
 */
class Observer
{
public:
        /**
         * @brief Default constructor
         */
        Observer() = default;
        /**
         * @brief Default destructor
         */
        virtual ~Observer() = default;
        /**
         * @brief Perform operation on trigger from Subject
         */
        virtual void onTrigger() = 0;
};
} // namespace Observer

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_OBSERVER_H
