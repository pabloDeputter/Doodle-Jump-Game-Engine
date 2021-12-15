//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERVIEW_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERVIEW_H

#include "IView.h"

/**
 * Namespace holds all Views
 */
namespace View {
/**
 * Class for view of Player Entity
 */
class PlayerView : public IView
{
public:
        /**
         * @brief Constructor of PlayerView object
         * @param entity Model::Entity - pointer to entity to be represented
         * @param window sf::RenderWindow - pointer to renderWindow where Sprite will be drawn on
         */
        PlayerView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window);
        /**
         * @brief Destructor of PlayerView object
         */
        ~PlayerView() override = default;
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERVIEW_H
