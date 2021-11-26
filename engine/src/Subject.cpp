//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Subject.h"

using namespace Observer;

void Subject::registerObserver(const std::shared_ptr<Observer>& observer) { mObservers.emplace_back(observer); }

void Subject::triggerObserver() const
{
        for (auto& i : mObservers) {
                i->onTrigger();
        }
}
