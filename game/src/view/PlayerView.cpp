//
// Created by Pablo Deputter on 19/11/2021.
//

#include "view/PlayerView.h"

using namespace View;

PlayerView::PlayerView(const std::shared_ptr<Model::Entity>& entity,
                             const std::shared_ptr<sf::RenderWindow>& window)
    : IView(entity, window)
{
        // Get texture associated with PlayerView from ResourceManager
        std::shared_ptr<sf::Texture>& tex =
            Utils::ResourceManager::getInstance().getTextures()->get(Utils::Type(Model::ePlayer));
        // Setup Sprite
        mSprite = std::make_unique<sf::Sprite>();
        mSprite->setTexture(*tex);
        mSprite->scale(2.f, 2.f);
        // Set width and height of Entity
        auto texSize = Utils::Camera::getInstance().inverseTransform(
            (float)tex->getSize().x * mSprite->getScale().x, (float)tex->getSize().y * mSprite->getScale().y);

        mEntity->setWidth(texSize.first);
        mEntity->setHeight(Utils::Camera::getInstance().getWorldDimensions().second - texSize.second);
}
