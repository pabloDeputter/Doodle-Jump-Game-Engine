//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_SUBJECT_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_SUBJECT_H

#include "Observer.h"

#include <algorithm>
#include <memory>
#include <vector>

/**
 * @brief Namespace holds observer pattern
 */
namespace Observer {
/**
 * @brief Class for Subject / Observable of observer pattern
 */
// template<class EventType, class Event>
class Subject
{
private:
        std::vector<std::shared_ptr<Observer>> mObservers; /**< std::vector containing Observers */
public:
        /**
         * @brief Default constructor
         */
        Subject() = default;
        /**
         * @brief Default destructor
         */
        virtual ~Subject() { mObservers.clear(); }
        /**
         * @brief Register Observer to mObservers
         * @param observer Observer to be added
         */
        void add(const std::shared_ptr<Observer>& observer) { mObservers.emplace_back(observer); }

        [[nodiscard]] const std::vector<std::shared_ptr<Observer>>& getObservers() const { return mObservers; }
        /**
         * @brief Clear all Observers from mObservers
         */
        void clear() { mObservers.clear(); }
        /**
         * @brief Trigger registered Observers
         */
        void trigger(EventType type, const std::shared_ptr<Event>& event) const
        {
                for (const auto& i : mObservers) {
                        i->onTrigger(type, event);
                }
        }
};
} // namespace Observer

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_SUBJECT_H
