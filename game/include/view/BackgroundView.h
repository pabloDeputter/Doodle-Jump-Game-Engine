//
// Created by Pablo Deputter on 29/11/2021.
//

#ifndef DOODLEJUMP_BACKGROUNDVIEW_H
#define DOODLEJUMP_BACKGROUNDVIEW_H

#include "IView.h"

namespace View {

class BackgroundView : public IView
{
public:
        BackgroundView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window)
            : IView(entity, window)
        {
                mTexture = std::make_unique<sf::Texture>();

                mTexture->loadFromFile("resource/Image/background_2.png");

                mSprite = std::make_unique<sf::Sprite>();
                mSprite->setTexture(*mTexture);
                mSprite->scale(.5f, .5f);

                mEntity->setWidth((float)mTexture->getSize().x * mSprite->getScale().x);
                mEntity->setHeight((float)mTexture->getSize().y * mSprite->getScale().y);
        }

        ~BackgroundView() override = default;
};
} // namespace View

#endif // DOODLEJUMP_BACKGROUNDVIEW_H
