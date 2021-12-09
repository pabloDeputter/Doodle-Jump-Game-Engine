//
// Created by Pablo Deputter on 29/11/2021.
//

#include "view/BackgroundView.h"

using namespace View;

void BackgroundView::handleEvent(const DrawEvent& event)
{
        auto const pos = Utils::Camera::getInstance().transform(mEntity->getX(),
                                                                mEntity->getY() - Utils::Camera::getInstance().getY());
        mSprite->setPosition(sf::Vector2f(pos.first, pos.second));
        mWindow->draw(*mSprite);
}

void BackgroundView::handleEvent(const OutOfViewEvent& event)
{
        mEntity->setY(mEntity->getY() +
                      Utils::Camera::getInstance().getWorldDimensions().second + 2.f);
}