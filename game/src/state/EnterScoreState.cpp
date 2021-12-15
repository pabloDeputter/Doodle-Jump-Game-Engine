//
// Created by Pablo Deputter on 16/12/2021.
//

#include "state/EnterScoreState.h"

using namespace States;
// TODo - ?
EnterScoreState::EnterScoreState(std::shared_ptr<sf::RenderWindow> window, Game& game) : State(std::move(window), game)
{
        mTitle.setFont(*Utils::ResourceManager::getInstance().getFonts()->get(Model::eScore));
        mTitle.setFillColor(sf::Color::Black);
        mTitle.setCharacterSize(30);
        mTitle.setString("-ENTER NAME-");
        sf::FloatRect bounds = mTitle.getLocalBounds();
        mTitle.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        mTitle.setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y - 600);

        mInfo = mTitle;
        mInfo.setFillColor(sf::Color::White);
        mInfo.setString("You achieved a new high score, type your\n name and press 'enter' if you are ready!");
        mInfo.setCharacterSize(19);
        mInfo.setLineSpacing(2.f);
        bounds = mInfo.getLocalBounds();
        mInfo.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        mInfo.setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y - 500);

        mName = mTitle;
        mName.setFillColor(sf::Color::White);
        mName.setString("|");
        mName.setCharacterSize(40);
        bounds = mName.getLocalBounds();
        mName.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        mName.setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y - 100);
}

void EnterScoreState::render() const
{
        mWindow->clear(sf::Color::Black);
        mWindow->draw(mTitle);
        mWindow->draw(mInfo);
        mWindow->draw(mName);
        mWindow->display();
}

void EnterScoreState::update()
{
        Utils::Utilities::setRainbowColor<sf::Text, sf::Color>(mTitle);

        //        static int blink = 0;

        mName.setString(mStringName);
        //        blink++;
        sf::FloatRect bounds = mName.getLocalBounds();
        mName.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        mName.setPosition(mWindow->getView().getCenter().x, mWindow->getView().getCenter().y - 100);
}

void EnterScoreState::processEvents()
{
        sf::Event event{};
        while (mWindow->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::BackSpace) {
                                if (mStringName.size() == 1 && mStringName[0] == '|') {
                                        std::cout << "lol\n";
                                }
                                mStringName = mStringName.substr(0, mStringName.size());
                        }
                        if (event.key.code == sf::Keyboard::Enter) {
                                HighScore::getInstance().add(
                                    std::make_shared<HighScoreData>(HighScore::getInstance().getToAdd(), mStringName));
                                mGame.mStateType = eMenu;
                                return;
                        }
                        break;
                case sf::Event::TextEntered:
                        if (event.text.unicode < 128) {
                                mStringName += static_cast<char>(event.text.unicode);
                        }
                        break;
                case sf::Event::Closed:
                        mWindow->close();
                        break;
                }
        }
}