//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H

#include "model/Bonus.h"
#include "model/Player.h"

#include "util/Camera.h"
#include "util/ResourceManager.h"

#include "observer/Events.h"
#include "observer/Observer.h"

#include "SFML/Graphics.hpp"

#include <iostream>
#include <memory>

/**
 * Namespace holds all Views
 */
namespace View {
/**
 * @brief Abstract class for View
 */
class IView : public Observer::Observer, public IEventHandler
{
protected:
        std::shared_ptr<Model::Entity> mEntity;             /**< Entity to be represented */
        std::unique_ptr<sf::Sprite> mSprite;                /**< Pointer to Sprite */
        std::shared_ptr<sf::RenderWindow> mWindow;          /**< Pointer to renderWindow */
private:
        /**
         * @brief On trigger of Subject
         * @param type EventType - type of event
         * @param event Event - Pointer to event
         */
        void onTrigger(EventType type, const std::shared_ptr<Event>& event) override { event->send(*this); }
        /**
         * @brief Handle DrawEvent event
         * @param event DrawEvent - event to be handled
         */
        void handleEvent(const DrawEvent& event) override;
        /**
         * @brief Handle OutOfView event
         * @param event OutOfView - event to be handled
         */
        void handleEvent(const OutOfViewEvent& event) override;
        /**
         * @brief Handle CollisionEvent event
         * @param event CollisionEvent - event to be handled
         */
        void handleEvent(const CollisionEvent& event) override {}
        /**
         * @brief Handle NewDifficultyEvent event
         * @param event NewDifficultyEvent - event to be handled
         */
        void handleEvent(const NewDifficultyEvent& event) override {}

        //        void handleEvent(const MoveEvent &event) override {}

public:
        /**
         * @brief Constructor for IView object
         * @param entity Model::Entity - pointer to entity to be represented
         * @param window sf::RenderWindow - pointer to renderWindow where Sprite will be drawn on
         */
        IView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window)
        {
                mEntity = entity;
                mWindow = window;
                mSprite = std::make_unique<sf::Sprite>();
        }
        /**
         * @brief Destructor for IView object
         */
        ~IView() override = default;
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H
