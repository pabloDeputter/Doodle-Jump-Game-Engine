//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_ICONTROLLER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_ICONTROLLER_H

#include "model/Entity.h"
#include "model/Player.h"

#include "util/Camera.h"

#include <memory>

/**
 * @brief Namespace holds all Controllers
 */
namespace Controller {
/**
 * @brief Abstract class for Controller
 */
class IController : public Observer::Observer, public IEventHandler
{
protected:
        std::shared_ptr<Model::Entity> mEntity; /**< Pointer to Entity */

private:
        /**
         * @brief On trigger of Subject
         * @param type EventType - type of event
         * @param event Event - Pointer to event
         */
        void onTrigger(EventType type, const std::shared_ptr<Event>& event) override { event->send(*this); }
        /**
         * @brief Handle KeyPressedEvent
         * @param event KeyPressedEvent
         */
        void handleEvent(const KeyPressedEvent& event) override {}
        /**
         * @brief Handle MoveEvent
         * @param event MoveEvent
         */
        void handleEvent(const MoveEvent& event) override
        {
                // Move Entity
                mEntity->move(event.isCollided());
                // If Entity is out of view --> trigger OutOfView event
                if (mEntity->getY() < Utils::Camera::getInstance().getY()) {
                        mEntity->trigger(EventType::OUT_OF_VIEW, std::make_shared<OutOfViewEvent>());
                        return;
                }
        }
        /**
         * @brief Handle CollisionEvent
         * @param event CollisionEvent
         */
        void handleEvent(const CollisionEvent& event) override {}

public:
        /**
         * @brief Default constructor for IController object
         */
        IController() = default;
        /**
         * @brief Constructor for IController object
         * @param entity Model::Entity - pointer to Entity to be controlled
         */
        explicit IController(std::shared_ptr<Model::Entity>& entity) : mEntity(entity) {}
        /**
         * @brief Default destructor for IController object
         */
        ~IController() override = default;
        /**
         * @brief Get Entity IController holds
         * @return Model::Entity - pointer to Entity
         */
        [[maybe_unused]] [[nodiscard]] const std::shared_ptr<Model::Entity>& getEntity() const { return mEntity; }
};
} // namespace Controller

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_ICONTROLLER_H
