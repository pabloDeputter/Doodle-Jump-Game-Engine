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
        virtual ~Subject() = default;
        /**
         * @brief Register Observer to mObservers
         * @param observer Observer
         */
        void add(const std::shared_ptr<Observer>& observer);
        /**
         * @brief Clear all Observers from mObservers
         */
        void clear();
        /**
         * @brief Trigger registered Observers
         */
        void trigger() const;
};
} // namespace Observer

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_SUBJECT_H
