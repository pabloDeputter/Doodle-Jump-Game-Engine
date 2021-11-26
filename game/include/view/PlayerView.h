//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERVIEW_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERVIEW_H

#include "IView.h"

namespace View {

class PlayerView : public IView
{
public:
        PlayerView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window)
            : IView(entity, window)
        {
                mTexture = std::make_unique<sf::Texture>();

                mTexture->loadFromFile("resource/Image/player.png");

                mSprite = std::make_unique<sf::Sprite>();
                mSprite->setTexture(*mTexture);
                mSprite->scale(2.f, 2.f);

                entity->setWidth((float)mTexture->getSize().x * 1.2f);
                entity->setHeight((float)mTexture->getSize().y * 1.5f);
        }

        //        PlayerView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>&
        //        window)
        //            : IView(entity, window)
        //        {
        //                std::cout << "lol\n";
        //                mTexture = std::make_unique<sf::Texture>();
        //                mTexture->loadFromFile("resource/Image/player.png");
        //        }

        PlayerView() = default;

        ~PlayerView() override = default;
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERVIEW_H
