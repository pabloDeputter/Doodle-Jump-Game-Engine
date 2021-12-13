//
// Created by Pablo Deputter on 19/11/2021.
//

#include "view/IView.h"

using namespace View;

IView::IView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window)
{
        mEntity = entity;
        mWindow = window;
        mSprite = std::make_unique<sf::Sprite>();
        mSound = std::make_unique<sf::Sound>();
}

void IView::drawCollisionBox()
{
        auto& c = Utils::Camera::getInstance();
        // Draw relatively from camera
        auto pos = c.transform(mEntity->getX(), mEntity->getY() - c.getY());

        auto size = c.transform(mEntity->getWidth(), mEntity->getHeight());

        // In sfml coördinates, maar berekenen in world coordinates
        float left = Utils::Camera::getInstance().transform(mEntity->getX(), 0.f).first;
        float top = Utils::Camera::getInstance().transform(0.f, mEntity->getY()).second;
        float width = size.first;
        float height = Utils::Camera::getInstance().getWindowDimensions().second - size.second;
        //        mSprite->setPosition(sf::Vector2f(left - (width / 2.f), pos.second));

        auto box = sf::RectangleShape();
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineThickness(2.f);
        box.setOutlineColor(sf::Color::Red);

        float y = top - (height / 2.f);
        //        std::cout << y << "\n";
        box.setPosition(left - (width / 2.f), pos.second);
        box.setSize(sf::Vector2f(width, height));

        //
        //        std::cout << "Box: " << box.getSize().x << "\n";
        //        std::cout << "Entity: " << Utils::Camera::getInstance().transform(mEntity->getWidth(), 0.f).first <<
        //        "\n"; std::cout << "Texture: " << mSprite->getTexture()->getSize().x * mSprite->getScale().x << "\n";

        //        std::cout << "Box: " << box.getPosition().x << "\n";
        //        std::cout << "Entity: " << Utils::Camera::getInstance().transform(mEntity->getX(), 0.f).first -
        //        (box.getSize().x / 2.f) << "\n"; std::cout << "Texture: " << mSprite->getPosition().x << "\n";

        mWindow->draw(box);
}

void IView::onTrigger(EventType type, const std::shared_ptr<Event>& event)
{
        event->send(*this);
}

void IView::handleEvent(const DrawEvent& event)
{
        auto const pos = Utils::Camera::getInstance().transform(mEntity->getX(),
                                                                mEntity->getY() - Utils::Camera::getInstance().getY());

        auto const size = Utils::Camera::getInstance().transform(mEntity->getWidth(), mEntity->getHeight());
        const float left = Utils::Camera::getInstance().transform(mEntity->getX(), 0.f).first;
        const float width = size.first;
        mSprite->setPosition(sf::Vector2f(left - (width / 2.f), pos.second));

        mWindow->draw(*mSprite);
}

void IView::handleEvent(const OutOfViewEvent& event)
{
        // If entity is out view it can be set to be destroyed
        mEntity->setRemoveFlag(true);
        // Clear observers
        mEntity->onDestroy();
}
