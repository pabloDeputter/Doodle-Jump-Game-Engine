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
#include <iostream>
void IView::onTrigger()
{
        // TODO - holy moly shieeeet
        auto& c = Utils::Camera::getInstance();
        //        auto p = c.transform(mEntity->getX(), mEntity->getY() - c.getPosition().second);
        auto p = c.transform(mEntity->getX(), mEntity->getY());

        mSprite->setPosition(sf::Vector2f(p.first, p.second));
        //        std::cout << "mSprite" << mSprite->getPosition().x << " : " << mSprite->getPosition().y << "\n";

        IView::onDraw();
}