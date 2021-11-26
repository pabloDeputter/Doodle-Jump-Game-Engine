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
#include <iostream>
void IView::onDraw() { mWindow->draw(*mSprite); }

void IView::onTrigger()
{
        mSprite->setPosition(sf::Vector2f(mEntity->getX(), mEntity->getY()));
        // TODO - remove - collision box
        //        auto rect = sf::RectangleShape();
        //        rect.setPosition(mSprite->getGlobalBounds().left, mSprite->getGlobalBounds().top);
        //        rect.setSize(sf::Vector2f(mEntity->getWidth(), mEntity->getHeight()));
        //        rect.setFillColor(sf::Color::Red);
        //        mWindow->draw(rect);
        IView::onDraw();
}