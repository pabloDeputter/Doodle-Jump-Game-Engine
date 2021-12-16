//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_OBSERVER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_OBSERVER_H

#include "Events.h"

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
         * @brief Default constructor for Observer object
         */
        Observer() = default;
        /**
         * @brief Default destructor for Observer object
         */
        virtual ~Observer() = default;
        /**
         * @brief On trigger from Subject registered to
         */
        virtual void onTrigger(EventType type, const std::shared_ptr<Event>& event) = 0;
};
} // namespace Observer

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_OBSERVER_H
