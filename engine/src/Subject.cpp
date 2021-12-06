//
// Created by Pablo Deputter on 14/11/2021.
//

#include "Subject.h"

using namespace Observer;

void Subject::add(const std::shared_ptr<Observer>& observer) { mObservers.emplace_back(observer); }

void Subject::remove(const std::shared_ptr<Observer>& observer) {}

void Subject::clear() { mObservers.clear(); }

void Subject::trigger() const
{
        for (const auto& i : mObservers) {
                i->onTrigger();
        }
}
