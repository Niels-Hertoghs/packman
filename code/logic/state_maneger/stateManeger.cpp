//
// Created by niels on 10/30/25.
//
#include <SFML/Graphics.hpp>
#include <memory>
#include "stateManeger.h"
#include <fstream>
#include <utility>
#include "../../render/notifications.h"
#include "../../world.h"


sf::Text makeText(const sf::Font& fontF, const std::string& text, double charSize, sf::Color color,double x, double y,const camera& cam) {
    sf::Text Text;
    Text.setFont(fontF);
    Text.setString(text);
    Text.setCharacterSize(cam.distanceToPixelsHeight(charSize));
    Text.setFillColor(color);

    // Zet origin wél met top en left in aanmerking genomen
    sf::FloatRect bounds = Text.getLocalBounds();
    Text.setOrigin((bounds.left + bounds.width) / 2.f,
                   (bounds.top  + bounds.height) / 2.f);

    // En pas dan pas de positie toe (zodat position refereert aan de nieuwe origin)
    auto Pos = cam.worldToPixel(x, y);
    Text.setPosition(static_cast<float>(Pos.first), static_cast<float>(Pos.second));

    return Text;
}
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

void stateManeger::runTop(sf::RenderWindow& window, sf::Event& event, camera& cam, std::shared_ptr<logic::world> wereld, const float& deltaTime) {
    stack.top().get()->run(window, event,*this,cam,std::move(wereld),deltaTime);
}


