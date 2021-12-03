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
                Model::Type type = entity->getType();
                std::shared_ptr<sf::Texture>& tex = Utils::Resourcemanager::getInstance().getTextures()->get(type);

                // TODO - remove sf::Texture member
                mSprite = std::make_unique<sf::Sprite>();
                mSprite->setTexture(*tex);
                mSprite->scale(.25f, .25f);

                //
                auto texSize = Utils::Camera::getInstance().inverseTransform(
                    (float)tex->getSize().x * mSprite->getScale().x, (float)tex->getSize().y * mSprite->getScale().y);

                // TODO - IntRect sprite sheet
                mEntity->setWidth(texSize.first);
                // TODO
                mEntity->setHeight(Utils::Camera::getInstance().getWorldDimensions().second - texSize.second);
        }

        PlatformView() = default;

        ~PlatformView() override = default;
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMVIEW_H
