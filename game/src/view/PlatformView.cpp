//
// Created by Pablo Deputter on 19/11/2021.
//

#include "view/PlatformView.h"

using namespace View;

PlatformView::PlatformView(const std::shared_ptr<Model::Entity>& entity,
                           const std::shared_ptr<sf::RenderWindow>& window)
    : IView(entity, window)
{
        // Get texture associated with PlatformView from ResourceManager
        int type = (int)entity->getType();
        std::shared_ptr<sf::Texture>& tex = Utils::ResourceManager::getInstance().getTextures()->get(Utils::Type(type));
        // Setup Sprite
        mSprite->setTexture(*tex);
        mSprite->scale(.22f, .22f);

        // TODO - sound
        //                mSound->setBuffer(*Utils::Resourcemanager::getInstance().getSounds()->get(mEntity->getType()));
        //                mSound->setVolume(100.f);
        // Set width and height of Entity based on Sprite dimensions
        auto texSize = Utils::Camera::getInstance().inverseTransform((float)tex->getSize().x * mSprite->getScale().x,
                                                                     (float)tex->getSize().y * mSprite->getScale().y);
        mEntity->setWidth(texSize.first);
        mEntity->setHeight(Utils::Camera::getInstance().getWorldDimensions().second - texSize.second);
}
