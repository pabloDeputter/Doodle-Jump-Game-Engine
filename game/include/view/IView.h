//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H

#include "model/Bonus.h"
#include "model/Player.h"

#include "Observer.h"
#include "util/Camera.h"

#include "util/Resourcemanager.h"

#include "SFML/Graphics.hpp"

#include "Event.h"

#include <iostream>
#include <memory>

namespace View {

class IView : public Observer::Observer, public IEventHandler
{
protected:
        std::shared_ptr<Model::Entity> mEntity;
        std::unique_ptr<sf::Sprite> mSprite;
        std::shared_ptr<sf::RenderWindow> mWindow;

public:
        IView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window);

        IView() = default;

        virtual ~IView() = default;

        void drawCollisionBox();

        void onTrigger(EventType type, const std::shared_ptr<Event>& event) override;

        void handleEvent(const DrawEvent& event) override;

        void handleEvent(const OutOfViewEvent& event) override;
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H
