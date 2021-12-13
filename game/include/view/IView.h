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

class IView : public Observer::Observer, public IEventHandler, public std::enable_shared_from_this<Observer::Observer>
{
protected:
        std::shared_ptr<Model::Entity> mEntity;
        std::unique_ptr<sf::Sprite> mSprite;
        std::shared_ptr<sf::RenderWindow> mWindow;
        std::unique_ptr<sf::Sound> mSound;

public:
        IView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window);

        IView() = default;

        virtual ~IView() = default;

        void drawCollisionBox();

        void onTrigger(EventType type, const std::shared_ptr<Event>& event) override;

        void handleEvent(const DrawEvent& event) override;

        void handleEvent(const OutOfViewEvent& event) override;

        virtual void handleEvent(const CollisionEvent& event) override {}

        void handleEvent(const NewDifficultyEvent& event) override {}

        template <class Type>
        static void setRainbowColor(const std::unique_ptr<sf::Text>& object)
        {
                if (object->getFillColor().r + 5 <= 255 && object->getFillColor().g == 0 &&
                    object->getFillColor().b == 0) {
                        object->setFillColor(sf::Color(object->getFillColor().r + 5, 0, 0));
                } else if (object->getFillColor().r == 255 && object->getFillColor().g + 5 <= 255 &&
                           object->getFillColor().b == 0) {
                        object->setFillColor(sf::Color(255, object->getFillColor().g + 5, 0));
                } else if (object->getFillColor().r - 5 >= 0 && object->getFillColor().g == 255 &&
                           object->getFillColor().b == 0) {
                        object->setFillColor(sf::Color(object->getFillColor().r - 5, 255, 0));
                } else if (object->getFillColor().r == 0 && object->getFillColor().g == 255 &&
                           object->getFillColor().b + 5 <= 255) {
                        object->setFillColor(sf::Color(0, 255, object->getFillColor().b + 5));
                } else if (object->getFillColor().r == 0 && object->getFillColor().g - 5 >= 0 &&
                           object->getFillColor().b == 255) {
                        object->setFillColor(sf::Color(0, object->getFillColor().g - 5, 255));
                } else if (object->getFillColor().r + 5 <= 255 && object->getFillColor().g == 0 &&
                           object->getFillColor().b == 255) {
                        object->setFillColor(sf::Color(object->getFillColor().r + 5, 0, 255));
                } else if (object->getFillColor().r == 255 && object->getFillColor().g == 0 &&
                           object->getFillColor().b - 5 >= 0) {
                        object->setFillColor(sf::Color(255, 0, object->getFillColor().b - 5));
                }
        }
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H
