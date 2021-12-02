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

                std::shared_ptr<sf::Texture>& tex =
                    Utils::Resourcemanager::getInstance().getTextures()->get(Model::ePlayer);

                mSprite = std::make_unique<sf::Sprite>();
                mSprite->setTexture(*tex);
                mSprite->scale(2.f, 2.f);

                entity->setWidth((float)tex->getSize().x * mSprite->getScale().x);
                entity->setHeight((float)tex->getSize().y * mSprite->getScale().y);
        }

        PlayerView() = default;

        ~PlayerView() override = default;
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERVIEW_H
