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
        std::unique_ptr<sf::Text> mLevelText;
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
                mDiffText->setCharacterSize(60);
                mDiffText->setFillColor(sf::Color::Black);

                mLevelText = std::make_unique<sf::Text>();
                mLevelText->setFont(*font);
                mLevelText->setCharacterSize(30);
                mLevelText->setFillColor(sf::Color::Black);
                mLevelText->setString("-NEW LEVEL REACHED-");
                sf::FloatRect bounds = mLevelText->getLocalBounds();
                mLevelText->setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
                const std::pair<float, float> windowDim = Utils::Camera::getInstance().getWindowDimensions();
                mLevelText->setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y - 375);
        }

        ~ScoreView() override = default;
};
} // namespace View

#endif // DOODLEJUMP_SCOREVIEW_H
