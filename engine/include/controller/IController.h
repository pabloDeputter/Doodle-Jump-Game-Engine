//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ICONTROLLER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ICONTROLLER_H

#include "model/Entity.h"
#include "model/Player.h"

#include <memory>

namespace Controller {

class IController : public Observer::Observer, public IEventHandler
{
protected:
        std::shared_ptr<Model::Entity> mEntity;

public:
        IController() = default;

        IController(std::shared_ptr<Model::Entity>& entity) : mEntity(entity) {}

        virtual ~IController() override = default;

        const std::shared_ptr<Model::Entity>& getEntity() const { return mEntity; }

        void onTrigger(EventType type, const std::shared_ptr<Event>& event) override { event->send(*this); }

        void handleEvent(const KeyPressedEvent& event) override {}

        void handleEvent(const MoveEvent& event) override;

        void handleEvent(const CollisionEvent& event) override {}
};
} // namespace Controller

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ICONTROLLER_H
