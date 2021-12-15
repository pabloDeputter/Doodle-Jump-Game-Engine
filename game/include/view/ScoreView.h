//
// Created by Pablo Deputter on 09/12/2021.
//

#ifndef DOODLEJUMP_SCOREVIEW_H
#define DOODLEJUMP_SCOREVIEW_H

#include "model/Score.h"

#include "IView.h"

/**
 * @brief Namespace holds all Views
 */
namespace View {
/**
 * @brief Class for View of Score Entity
 */
class ScoreView : public IView
{
private:
        std::unique_ptr<sf::Text> mScoreText; /**< sf::Text for Score */
        std::unique_ptr<sf::Text> mLevelText; /**< sf::Text for Level */
        std::unique_ptr<sf::Text> mDiffText;  /**< sf::Text for Difficulty */

private:
        /**
         * @brief Handle DrawEvent event
         * @param event DrawEvent - event to be handled
         */
        void handleEvent(const DrawEvent& event) override;
        /**
         * @brief Handle NewDifficultyEvent
         * @param event NewDifficultyEvent - event to be handled
         */
        void handleEvent(const NewDifficultyEvent& event) override;

public:
        /**
         * @brief Constructor of ScoreView object
         * @param entity Model::Entity - pointer to entity to be represented
         * @param window sf::RenderWindow - pointer to renderWindow where Sprite will be drawn on
         */
        ScoreView(std::shared_ptr<Model::Score>& entity, const std::shared_ptr<sf::RenderWindow>& window);
        /**
         * @brief Destructor of ScoreView object
         */
        ~ScoreView() override = default;
};
} // namespace View

#endif // DOODLEJUMP_SCOREVIEW_H
