//
// Created by Pablo Deputter on 29/11/2021.
//

#ifndef DOODLEJUMP_BACKGROUNDVIEW_H
#define DOODLEJUMP_BACKGROUNDVIEW_H

#include "IView.h"

#include <filesystem>

namespace View {

class BackgroundView : public IView
{
public:
        BackgroundView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window)
            : IView(entity, window)
        {
                std::shared_ptr<sf::Texture>& tex =
                    Utils::Resourcemanager::getInstance().getTextures()->get(Model::eBackground);

                mSprite = std::make_unique<sf::Sprite>();
                mSprite->setTexture(*tex);
                mSprite->scale(1.f, 1.f);
                mSprite->setColor(sf::Color(255, 255, 255, 255));

                mEntity->setWidth((float)tex->getSize().x * mSprite->getScale().x);
                mEntity->setHeight((float)tex->getSize().y * mSprite->getScale().y);
                mEntity->setHeight(mEntity->getHeight());
        }

        ~BackgroundView() override = default;
};
} // namespace View

#endif // DOODLEJUMP_BACKGROUNDVIEW_H
