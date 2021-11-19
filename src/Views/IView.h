//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H

#include "../Models/Entity/Entity.h"
#include "../Models/Entity/Player.h"

#include "../Observer/Observer.h"

#include "SFML/Graphics.hpp"
#include <memory>

namespace View {

class IView : public Observer::Observer
{
protected:
        std::shared_ptr<Model::Entity> mEntity;
        std::unique_ptr<sf::Sprite> mSprite;
        std::unique_ptr<sf::Texture> mTexture;

        std::shared_ptr<sf::RenderWindow> mWindow;

public:
        IView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window,
              const std::string& path);

        IView() = default;

        virtual ~IView() = default;

        virtual void onDraw();

        virtual void onUpdate();
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H
