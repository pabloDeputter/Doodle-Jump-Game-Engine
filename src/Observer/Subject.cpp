//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Subject.h"

using namespace Observer;

void Subject::registerObserver(const std::shared_ptr<Observer>& observer) { mObservers.emplace_back(observer); }

void Subject::removeObserver(const std::shared_ptr<Observer>& observer)
{
        std::erase_if(mObservers, [observer](const std::shared_ptr<Observer>& x) { return x == observer; });
}

void Subject::notifyObserver() const
{
        for (auto& i : mObservers) {
                i->update();
        }
}