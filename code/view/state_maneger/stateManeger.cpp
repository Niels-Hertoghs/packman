//
// Created by niels on 10/30/25.
//
#include <SFML/Graphics.hpp>
#include <memory>
#include "stateManeger.h"
#include <fstream>
#include <utility>
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

void stateManeger::pop2State() {
    if (!stack.empty()) {
        stack.pop();
    }
    if (!stack.empty()) {
        stack.pop();
    }
}

std::unique_ptr<view::state> stateManeger::getCurrentState() {
    if (stack.empty())
        return nullptr;
    return std::move(stack.top());
}

void stateManeger::runTop(sf::RenderWindow& window, sf::Event& event, view::camera& cam,
                          std::shared_ptr<logic::world> wereld, const float& deltaTime) {
    std::pair<std::vector<sf::Text>, std::vector<sf::RectangleShape>> result = stack.top().get()->run(
        window, event, *this, cam, std::move(wereld), deltaTime);
    // alles op het scherm afdrukken
    // eerst de buttens = rechthoek met een texture
    // vervolgens de text, zodat de text op de butten wordt gezet en je het kan lezen ( anders gaat de butten over de text en kan je het niet lezen).
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

void stateManeger::startVictory() {
    std::unique_ptr<view::VictoryState> state = std::make_unique<view::VictoryState>();
    pushStateAndDelete(std::move(state));
}

void stateManeger::gameOverState() {
    prevState();
    std::unique_ptr<view::gameOverState> state = std::make_unique<view::gameOverState>();
    pushState(std::move(state));
}

}
