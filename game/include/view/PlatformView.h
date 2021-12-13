//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMVIEW_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMVIEW_H

#include "IView.h"
#include <thread>

namespace View {

class PlatformView : public IView
{
public:
        PlatformView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window)
            : IView(entity, window)
        {
                Model::Type type = entity->getType();
                std::shared_ptr<sf::Texture>& tex = Utils::Resourcemanager::getInstance().getTextures()->get(type);

                mSprite->setTexture(*tex);
                mSprite->scale(.25f, .25f);

                // TODO - sound
                //                mSound->setBuffer(*Utils::Resourcemanager::getInstance().getSounds()->get(mEntity->getType()));
                //                mSound->setVolume(100.f);

                auto texSize = Utils::Camera::getInstance().inverseTransform(
                    (float)tex->getSize().x * mSprite->getScale().x, (float)tex->getSize().y * mSprite->getScale().y);

                mEntity->setWidth(texSize.first);
                mEntity->setHeight(Utils::Camera::getInstance().getWorldDimensions().second - texSize.second);
        }

        PlatformView() = default;

        ~PlatformView() override = default;

        void handleEvent(const CollisionEvent& event) override
        {
                // TODO - threads leaks
                //                mSound->play();
        }
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMVIEW_H
