//
// Created by Pablo Deputter on 19/11/2021.
//

#include "view/IView.h"

using namespace View;

IView::IView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window)
{
        mEntity = entity;
        mWindow = window;
}

void IView::onDraw() { mWindow->draw(*mSprite); }

void IView::onTrigger()
{
        auto p = Utils::Camera::getInstance().transform(mEntity->getX(), mEntity->getY());

        mSprite->setPosition(sf::Vector2f(p.first, p.second));

        IView::onDraw();
}