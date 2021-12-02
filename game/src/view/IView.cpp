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
        // TODO - delete (weak pointers)
        if (mEntity->getY() < Utils::Camera::getInstance().getY()) {
                //                if (mEntity->getType() == Model::eBackground) std::cout << "lol\n";
                mEntity->onInvisible();
                return;
        }

        auto& c = Utils::Camera::getInstance();
        //        auto p = c.transform(mEntity->getX() - c.getX(), mEntity->getY() - c.getY());
        // Draw relatively from camera
        auto p = c.transform(mEntity->getX(), mEntity->getY() - c.getY());

        // TODO - camera.pos() == player.pos()
        mSprite->setPosition(sf::Vector2f(p.first, p.second));

        // TODO - check sprite pos bij een large nummber
        IView::onDraw();

        //        IView::onDraw();
}