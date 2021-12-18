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
class Subject
{
protected:
        std::vector<std::shared_ptr<Observer>> mObservers; /**< std::vector containing Observers */
public:
        /**
         * @brief Default constructor for Subject object
         */
        Subject() = default;
        /**
         * @brief Destructor for Subject object
         */
        virtual ~Subject() { mObservers.clear(); }
        /**
         * @brief Register Observer to list
         * @param observer Observer - observer to be added to list
         */
        void add(const std::shared_ptr<Observer>& observer) { mObservers.emplace_back(observer); }
        /**
         * @brief Get registered Observers
         * @return std::vector - list of registered observers
         */
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
                // Traverse registered observers
                for (const auto& i : mObservers) {
                        // Trigger event
                        i->onTrigger(type, event);
                }
        }
};
} // namespace Observer

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_SUBJECT_H
