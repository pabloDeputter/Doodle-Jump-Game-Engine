//
// Created by Pablo Deputter on 19/11/2021.
//

#include "view/IView.h"

using namespace View;

void IView::handleEvent(const DrawEvent& event)
{
        // Transform Entity pos. to screen coordinates
        auto const pos = Utils::Camera::getInstance().transform(mEntity->getX(),
                                                                mEntity->getY() - Utils::Camera::getInstance().getY());

        auto const size = Utils::Camera::getInstance().transform(mEntity->getWidth(), mEntity->getHeight());
        const float left = Utils::Camera::getInstance().transform(mEntity->getX(), 0.f).first;
        const float width = size.first;
        // Position sprite so it is placed with its origin the position of Entity
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
