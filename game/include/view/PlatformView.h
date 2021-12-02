//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMVIEW_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMVIEW_H

#include "IView.h"

#include "model/Platform.h"

namespace View {

class PlatformView : public IView
{
public:
        PlatformView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window)
            : IView(entity, window)
        {
                mTexture = std::make_unique<sf::Texture>();

                auto& resManager = Utils::Resourcemanager::getInstance();

                Model::Type type = entity->getType();
                std::shared_ptr<sf::Texture>& tex = resManager.getTextures()->get(type);

                // TODO - remove sf::Texture member
                mSprite = std::make_unique<sf::Sprite>();
                mSprite->setTexture(*tex);
                mSprite->scale(.25f, .25f);

                // TODO - IntRect sprite sheet
                entity->setWidth((float)mTexture->getSize().x * .25f);
                entity->setHeight((float)mTexture->getSize().y * .25f);
        }

        PlatformView() = default;

        ~PlatformView() override = default;
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMVIEW_H
