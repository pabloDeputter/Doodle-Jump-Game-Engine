//
// Created by Pablo Deputter on 09/12/2021.
//

#ifndef DOODLEJUMP_SCOREVIEW_H
#define DOODLEJUMP_SCOREVIEW_H

#include "IView.h"

#include "Score.h"

namespace View {

class ScoreView : public IView
{
private:
        std::unique_ptr<sf::Text> mText;
        std::unique_ptr<sf::Text> mDiffText;

        void handleEvent(const DrawEvent& event) override;

        void handleEvent(const NewDifficultyEvent& event) override;

public:
        ScoreView(std::shared_ptr<Model::Score>& entity, const std::shared_ptr<sf::RenderWindow>& window)
            : IView(entity, window)
        {
                std::shared_ptr<sf::Font>& font = Utils::Resourcemanager::getInstance().getFonts()->get(Model::eScore);

                mSprite = std::make_unique<sf::Sprite>();
                mText = std::make_unique<sf::Text>();
                mText->setFont(*font);
                mText->setFillColor(sf::Color::Black);

                mDiffText = std::make_unique<sf::Text>();
                mDiffText->setFont(*font);
                mDiffText->setFillColor(sf::Color::Red);
        }

        ~ScoreView() override = default;
};
} // namespace View

#endif // DOODLEJUMP_SCOREVIEW_H
