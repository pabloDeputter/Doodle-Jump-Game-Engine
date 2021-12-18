//
// Created by Pablo Deputter on 06/12/2021.
//

#include "view/BonusView.h"

using namespace View;

BonusView::BonusView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window)
    : IView(entity, window)
{
        // Get texture associated with BonusView from ResourceManager
        int type = (int)entity->getType();
        std::shared_ptr<sf::Texture>& tex = Utils::ResourceManager::getInstance().getTextures()->get(Utils::Type(type));

        // Setup Sprite
        mSprite = std::make_unique<sf::Sprite>();
        mSprite->setTexture(*tex);
        mSprite->scale(.1, .1f);

        // Set width and height of Entity based on Sprite dimensions
        auto texSize = Utils::Camera::getInstance().inverseTransform((float)tex->getSize().x * mSprite->getScale().x,
                                                                     (float)tex->getSize().y * mSprite->getScale().y);
        mEntity->setWidth(texSize.first);
        mEntity->setHeight(Utils::Camera::getInstance().getWorldDimensions().second - texSize.second);
}