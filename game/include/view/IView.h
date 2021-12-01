//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H

#include "model/Entity.h"
#include "model/Player.h"

#include "Observer.h"
#include "util/Camera.h"

#include "util/Resourcemanager.h"

#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>

namespace Observer {
class Subject;
}

namespace View {

class IView : public Observer::Observer
{
protected:
        std::shared_ptr<Model::Entity> mEntity;
        std::unique_ptr<sf::Sprite> mSprite;

        // TODO --> apart texture class?
        std::unique_ptr<sf::Texture> mTexture;

        std::shared_ptr<sf::RenderWindow> mWindow;

public:
        IView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window);

        IView() = default;

        virtual ~IView() = default;

        virtual void onDraw();

        virtual void onTrigger();
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H
