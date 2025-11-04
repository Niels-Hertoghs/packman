//
// Created by niels on 10/30/25.
//
#include <SFML/Graphics.hpp>
#include <memory>
#include "stateManeger.h"

sf::Text makeText(const sf::Font& fontF, const std::string& text, int charSize, sf::Color color,int x, int y) {
    sf::Text menuText;
    menuText.setFont(fontF);
    menuText.setString(text);
    menuText.setCharacterSize(charSize);
    menuText.setFillColor(color);
    menuText.setPosition(x,y);
    return menuText;
}

stateManeger::stateManeger() {
    pushState(std::make_unique<menuState>());
}


void stateManeger::pushState(std::unique_ptr<state> newState) {
    stack.push(std::move(newState));
}

void stateManeger::prevState() {
    if (!stack.empty()) {
        stack.pop();
    }
}

std::unique_ptr<state> stateManeger::getCurrentState() {
    if (stack.empty()) return nullptr;
    return std::move(stack.top());
}

void stateManeger::runTop(sf::RenderWindow& window, sf::Event& event, const camera& cam) {
    stack.top().get()->run(window, event,*this,cam);
}


// menu state
void menuState::run(sf::RenderWindow& window, sf::Event& event,stateManeger& manager, const camera& cam) {

    //lettertype inladen
    sf::Font packmanFont;
    if (!packmanFont.loadFromFile("input_output/packman_font.ttf")) {
        std::cerr << "Kon het lettertype niet laden!" << std::endl;
    }

    // menu title maken
    std::pair<int,int> menuPos = cam.worldToPixel(0.55f, 0.525f);
    sf::Text menuText = makeText(packmanFont, "Menu", 60, sf::Color::Yellow, menuPos.first, menuPos.second);
    sf::Text highscoreText = makeText(packmanFont, "Previous High score: " + std::to_string(60), 20, sf::Color::White, 280, 150);
    sf::FloatRect bounds = menuText.getLocalBounds();
    menuText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    //de play butten
    sf::RectangleShape playButton(sf::Vector2f(300, 100));
    playButton.setFillColor(sf::Color::Green);
    playButton.setPosition(250, 250);

    sf::Text playText = makeText(packmanFont, "Play", 60, sf::Color::Magenta, 320, 50);
    // Tekst centreren in de knop
    sf::FloatRect textRect = playText.getLocalBounds();
    playText.setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top + textRect.height / 2.0f);
    playText.setPosition(
        playButton.getPosition().x + playButton.getSize().x / 2.0f,
        playButton.getPosition().y + playButton.getSize().y / 2.0f
    );

    if (event.type == sf::Event::MouseButtonPressed &&
         event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (playButton.getGlobalBounds().contains(mousePos)) {
            //TODO: zou de ander moeten oproepen
            manager.pushState(std::make_unique<LevelState>());

        }
    }

    window.draw(menuText);
    window.draw(highscoreText);
    window.draw(playButton);
    window.draw(playText);
}

void LevelState::run(sf::RenderWindow &window, sf::Event &event, stateManeger &manager, const camera& cam) {
    sf::Font arialFont;
    if (!arialFont.loadFromFile("input_output/arial.ttf")) {
        std::cerr << "Kon het lettertype niet laden!" << std::endl;
    }

    // de pagina naam en de prev hisgh score afdrrukken
    sf::Text menuText = makeText(arialFont, "Menu", 60, sf::Color::Yellow, 320, 50);
    window.draw(menuText);

}

