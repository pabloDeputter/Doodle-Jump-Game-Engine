//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMVIEW_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMVIEW_H

#include "IView.h"

#include "model/Platform.h"

namespace View {

class PlatformView : public IView
{
public:
        PlatformView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window)
            : IView(entity, window)
        {
                mTexture = std::make_unique<sf::Texture>();

                if (std::dynamic_pointer_cast<Model::Platform>(entity)->getSort() == Model::Platform::eStatic) {
                        mTexture->loadFromFile("resource/Image/platform_1.png");
                } else if (std::dynamic_pointer_cast<Model::Platform>(entity)->getSort() ==
                           Model::Platform::eHorizontal) {
                        mTexture->loadFromFile("resource/Image/platform_2.png");
                } else if (std::dynamic_pointer_cast<Model::Platform>(entity)->getSort() ==
                           Model::Platform::eVertical) {
                        mTexture->loadFromFile("resource/Image/platform_3.png");
                } else if (std::dynamic_pointer_cast<Model::Platform>(entity)->getSort() ==
                           Model::Platform::eTemporary) {
                        mTexture->loadFromFile("resource/Image/platform_4.png");
                }

                mSprite = std::make_unique<sf::Sprite>();
                mSprite->setTexture(*mTexture);
                mSprite->scale(.3f, .3f);

                // TODO - IntRect sprite sheet
                entity->setWidth((float)mTexture->getSize().x * .2f);
                entity->setHeight((float)mTexture->getSize().y * .2f);
        }

        PlatformView() = default;

        ~PlatformView() override = default;
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMVIEW_H
