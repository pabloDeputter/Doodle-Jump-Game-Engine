//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMVIEW_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMVIEW_H

#include "IView.h"

/**
 * @brief Namespace holds all Views
 */
namespace View {
/**
 * @brief Class for View of Platform Entity
 */
class PlatformView : public IView
{
private:
        /**
         * @brief Handle CollisionEvent event
         * @param event CollisionEvent - event to handle
         */
        void handleEvent(const CollisionEvent& event) override {}

public:
        /**
         * @brief Constructor of PlatformView object
         * @param entity Model::Entity - pointer to entity to be represented
         * @param window sf::RenderWindow - pointer to renderWindow where Sprite will be drawn on
         */
        PlatformView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window);
        /**
         * @brief Destructor of PlatformView object
         */
        ~PlatformView() override = default;
};
} // namespace View

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMVIEW_H
