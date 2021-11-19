//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H

#include "../Models/Entity/Entity.h"
#include "../Observer/Observer.h"

#include "SFML/Graphics.hpp"
#include <memory>

namespace View {

class IView : public Observer::Observer
{
private:
        std::shared_ptr<Model::Entity> mEntity;
        std::unique_ptr<sf::Sprite> mSprite;
        std::unique_ptr<sf::Texture> mTexture;

public:
        IView() = default;

        virtual ~IView() = default;
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_IVIEW_H
