//
// Created by Pablo Deputter on 18/12/2021.
//

#include "state/SettingState.h"

#include "util/Utilities.h"

#include <utility>

using namespace States;
using namespace Utils;

SettingState::SettingState(std::shared_ptr<sf::RenderWindow> window, Game& game, Settings::Difficulty diff)
    : State(std::move(window), game), mSelected(diff)
{
        // Create text
        sf::Text easy;
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuSettings),
                            sf::Color::White, 40, easy, "EASY");
        sf::Text normal;
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuSettings),
                            sf::Color::White, 40, normal, "NORMAL");
        sf::Text difficult;
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuSettings),
                            sf::Color::White, 40, difficult, "DIFFICULT");
        sf::Text hard;
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuSettings),
                            sf::Color::White, 40, hard, "HARD");
        sf::Text insane;
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuSettings),
                            sf::Color::White, 40, insane, "INSANE");
        sf::Text extreme;
        Utilities::initText(*Utils::ResourceManager::getInstance().getFonts()->get(Type::eMenuSettings),
                            sf::Color::White, 40, extreme, "EXTREME");
        // Initialize std::vector containing settings
        mSettings = {easy, normal, difficult, hard, insane, extreme};

        // Highlight selected setting
        mSettings[diff].setFillColor(sf::Color(204, 46, 30));

        // Spacing between each setting displayed
        float factor_setting = 1.f;
        // Positioning of setting
        for (auto& i : mSettings) {
                i.setPosition(mWindow->getView().getCenter().x,
                              mWindow->getView().getCenter().y * 0.8f * factor_setting);
                factor_setting += .090f;
        }
}

void SettingState::update()
{
        // Set color of every sf::Text setting to white
        for (auto& i : mSettings) {
                i.setFillColor(sf::Color::White);
        }
        // Highlight selected setting to RED
        mSettings[mSelected].setFillColor(sf::Color(204, 46, 30));
}

void SettingState::handleInput(sf::Keyboard::Key key, bool isPressed)
{
        if (key == sf::Keyboard::Return && isPressed) {
                mGame.popState();
                mGame.peekState()->setNewDiff(mSelected);
        } else if (key == sf::Keyboard::Up && isPressed) {
                if (mSelected == 0) {
                        mSelected = mSettings.size() - 1;
                } else {
                        mSelected--;
                }
                // If we go over the index of the last element we will get a segmentation fault, so we set
                // mSelected equal to zero.
        } else if (key == sf::Keyboard::Down && isPressed) {
                mSelected++;
                // If mSelected is equal we and we want to decrease the value of it, it shall point to a non-existing
                // element inside mInfo, so we set mSelected equal to the index of the last element.
                if (mSelected > mSettings.size() - 1) {
                        mSelected = 0;
                }
        }
}

void SettingState::processEvents()
{
        sf::Event event{};
        while (mWindow->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::KeyPressed:
                        handleInput(event.key.code, true);
                        break;
                case sf::Event::KeyReleased:
                        handleInput(event.key.code, false);
                        break;
                case sf::Event::Closed:
                        mWindow->close();
                        break;
                }
        }
}