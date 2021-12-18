//
// Created by Pablo Deputter on 29/11/2021.
//

#include "view/BackgroundView.h"

using namespace View;

BackgroundView::BackgroundView(const std::shared_ptr<Model::Entity>& entity,
                               const std::shared_ptr<sf::RenderWindow>& window)
    : IView(entity, window)
{
        // Get texture associated with BackgroundView from ResourceManager
        std::shared_ptr<sf::Texture>& tex =
            Utils::ResourceManager::getInstance().getTextures()->get(Utils::Type(Model::eBackground));

        // Setup Sprite
        mSprite = std::make_unique<sf::Sprite>();
        mSprite->setTexture(*tex);
        mSprite->scale(1.f, 1.f);
        mSprite->setColor(sf::Color(255, 255, 255, 255));

        // Set width and height of Entity based on Sprite dimensions
        auto texSize = Utils::Camera::getInstance().inverseTransform((float)tex->getSize().x * mSprite->getScale().x,
                                                                     (float)tex->getSize().y * mSprite->getScale().y);

        mEntity->setWidth(texSize.first);
        mEntity->setHeight(Utils::Camera::getInstance().getWorldDimensions().second - texSize.second);
}

void BackgroundView::handleEvent(const DrawEvent& event)
{
        // Transform position of Entity based on pos. of Camera
        auto const pos = Utils::Camera::getInstance().transform(mEntity->getX(),
                                                                mEntity->getY() - Utils::Camera::getInstance().getY());
        mSprite->setPosition(sf::Vector2f(pos.first, pos.second));
        mWindow->draw(*mSprite);
}

void BackgroundView::handleEvent(const OutOfViewEvent& event)
{
        // Move Background tile up, so that every tile gets recycled as the
        // Player moves up in the World
        mEntity->setY(mEntity->getY() + Utils::Camera::getInstance().getWorldDimensions().second + 2.f);
}