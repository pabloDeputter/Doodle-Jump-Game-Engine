//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_SUBJECT_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_SUBJECT_H

#include "Observer.h"

#include <algorithm>
#include <vector>

namespace Observer {

class Subject
{
protected:
        std::vector<std::shared_ptr<Observer>> mObservers;

public:
        Subject() = default;

        virtual ~Subject() = default;

        void registerObserver(const std::shared_ptr<Observer>& observer);

        ////        void removeObserver(const std::shared_ptr<Observer>& observer);

        void notifyObserver() const;
};
} // namespace Observer

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_SUBJECT_H
