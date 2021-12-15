//
// Created by Pablo Deputter on 06/12/2021.
//

#ifndef DOODLEJUMP_BONUSVIEW_H
#define DOODLEJUMP_BONUSVIEW_H

#include "IView.h"

/**
 * @brief Namespace holds all Views
 */
namespace View {
/**
 * @brief Class for View of Bonus Entity
 */
class BonusView : public IView
{
public:
        /**
         * @brief Constructor of BonusView object
         * @param entity Model::Entity - pointer to entity to be represented
         * @param window sf::RenderWindow - pointer to renderWindow where Sprite will be drawn on
         */
        BonusView(const std::shared_ptr<Model::Entity>& entity, const std::shared_ptr<sf::RenderWindow>& window);
        /**
         * @brief Destructor of BonusView
         */
        ~BonusView() override = default;
};
} // namespace View

#endif // DOODLEJUMP_BONUSVIEW_H
