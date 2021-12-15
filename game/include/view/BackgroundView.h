//
// Created by Pablo Deputter on 29/11/2021.
//

#ifndef DOODLEJUMP_BACKGROUNDVIEW_H
#define DOODLEJUMP_BACKGROUNDVIEW_H

#include "IView.h"

/**
 * @brief Namespace holds all Views
 */
namespace View {
/**
 * @brief Class for View of Background Entity
 */
class BackgroundView : public IView
{
private:
        /**
         * @brief Handle DrawEvent event
         * @param event DrawEvent - event to be handled
         */
        void handleEvent(const DrawEvent& event) override;
        /**
         * @brief Handle OutOfView event
         * @param event OutOfView - event to be handled
         */
        void handleEvent(const OutOfViewEvent& event) override;

public:
        /**
         * @brief Constructor of BackgroundView
         * @param entity Model::Entity - pointer to entity to be represented
         * @param window sf::RenderWindow - pointer to renderWindow where Sprite will be drawn on
         */
        BackgroundView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window);
        /**
         * @brief Destructor of BackgroundView
         */
        ~BackgroundView() override = default;
};
} // namespace View

#endif // DOODLEJUMP_BACKGROUNDVIEW_H
