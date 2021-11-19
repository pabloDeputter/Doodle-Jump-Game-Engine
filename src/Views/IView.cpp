//
// Created by Pablo Deputter on 19/11/2021.
//

#include "IView.h"

using namespace View;

IView::IView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window,
             const std::string& path)
{
        mEntity = entity;
        mWindow = window;
        mTexture = std::make_unique<sf::Texture>();

        try {
                mTexture->loadFromFile(path);
                throw "Texture couldn't be loaded!\n";
        } catch (...) {
        }

        mSprite = std::make_unique<sf::Sprite>();
        mSprite->setTexture(*mTexture);
}

void IView::onDraw()
{
        std::cout << "IView::onDraw()\n";
        mWindow->draw(*mSprite);
}

void IView::onUpdate()
{
        //        std::cout << "IView::onUpdate()\n";
        mSprite->setPosition(sf::Vector2f(mEntity->getX(), mEntity->getY()));
}