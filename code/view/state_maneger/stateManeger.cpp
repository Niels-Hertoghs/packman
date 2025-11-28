//
// Created by niels on 10/30/25.
//
#include <SFML/Graphics.hpp>
#include <memory>
#include "stateManeger.h"
#include <fstream>
#include <utility>
#include "../../view/notifications.h"
#include "../../logic/world.h"

namespace view {
    /// ---------------------------------------------------------------------------------------------------------------
    /// @class stateManeger
    /// ---------------------------------------------------------------------------------------------------------------

    stateManeger::stateManeger() {
        pushState(std::make_unique<view::menuState>());
    }

    void stateManeger::pushState(std::unique_ptr<view::state> newState) {
        stack.push(std::move(newState));
    }

    void stateManeger::prevState() {
        if (!stack.empty()) {
            stack.pop();
        }
    }

    std::unique_ptr<view::state> stateManeger::getCurrentState() {
        if (stack.empty()) return nullptr;
        return std::move(stack.top());
    }

    void stateManeger::runTop(sf::RenderWindow& window, sf::Event& event, view::camera& cam, std::shared_ptr<logic::world> wereld, const float& deltaTime) {
        std::pair<std::vector<sf::Text>,std::vector<sf::RectangleShape>> result = stack.top().get()->run(window, event,*this,cam,std::move(wereld),deltaTime);
        for (auto& rechthoek : result.second) {
            window.draw(rechthoek);
        }
        for (auto& Text : result.first) {
            window.draw(Text);
        }
    }

    void stateManeger::pushStateAndDelete(std::unique_ptr<view::state> newState) {
        if (!stack.empty()) {
            stack.pop();
        }
        stack.push(std::move(newState));
    }
}

