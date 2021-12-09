//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_OBSERVER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_OBSERVER_H

#include "Event.h"

#include <memory>

/**
 * @brief Namespace holds Observer pattern
 */
namespace Observer {
/**
 * @brief Class for Observer of Observer pattern
 */
// template<class EventType, class DataType>
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
        virtual void onTrigger(EventType type, const std::shared_ptr<Event>& event) = 0;
};
} // namespace Observer

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_OBSERVER_H
