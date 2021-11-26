//
// Created by Pablo Deputter on 14/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_OBSERVER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_OBSERVER_H

namespace Observer {
/**
 * @brief Class for Observer object
 */
class Observer
{
public:
        Observer() = default;

        virtual ~Observer() = default;

        virtual void onTrigger() = 0;
};
} // namespace Observer

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_OBSERVER_H
