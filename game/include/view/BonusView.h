//
// Created by Pablo Deputter on 06/12/2021.
//

#ifndef DOODLEJUMP_BONUSVIEW_H
#define DOODLEJUMP_BONUSVIEW_H

#include "IView.h"

namespace View {

class BonusView : public IView
{
public:
        BonusView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window)
            : IView(entity, window)
        {
                Model::Type type = entity->getType();
                std::shared_ptr<sf::Texture>& tex = Utils::Resourcemanager::getInstance().getTextures()->get(type);

                std::cout << type << "\n";

                mSprite = std::make_unique<sf::Sprite>();
                mSprite->setTexture(*tex);
                mSprite->scale(.1, .1f);

                auto texSize = Utils::Camera::getInstance().inverseTransform(
                    (float)tex->getSize().x * mSprite->getScale().x, (float)tex->getSize().y * mSprite->getScale().y);

                mEntity->setWidth(texSize.first);
                mEntity->setHeight(Utils::Camera::getInstance().getWorldDimensions().second - texSize.second);
        }

        BonusView() = default;

        ~BonusView() override = default;
};
} // namespace View

#endif // DOODLEJUMP_BONUSVIEW_H
