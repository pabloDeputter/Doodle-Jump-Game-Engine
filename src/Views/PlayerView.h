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
        PlayerView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window,
                   const std::string& path)
            : IView(entity, window, path)
        {
        }

        PlayerView() = default;

        ~PlayerView() override = default;
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERVIEW_H
