//
// Created by niels on 10/30/25.
//
#include <SFML/Graphics.hpp>
#include "stateManeger.h"

sf::Text makeText(const sf::Font& fontF, const std::string& text, int charSize, sf::Color color, float x, float y) {
    sf::Text menuText;
    menuText.setFont(fontF);
    menuText.setString(text);
    menuText.setCharacterSize(charSize);
    menuText.setFillColor(color);
    menuText.setPosition(x, y);
    return menuText;
}

stateManeger::stateManeger() = default;

void stateManeger::start() {
    pushState(std::make_unique<menuState>());
}

void stateManeger::levelState() {
    pushState(std::make_unique<LevelState>());
}


void stateManeger::pushState(std::unique_ptr<state> newState) {
    states.push(std::move(newState));
}

void stateManeger::popState() {
    if (!states.empty()) {
        states.pop();
    }
}

state* stateManeger::getCurrentState() {
    if (states.empty()) return nullptr;
    return states.top().get();
}


// menu state
menuState::menuState() {
    //TODO: highscore uitlezen uit bestand.
    int prevHigh = 300;

    sf::RenderWindow window(sf::VideoMode(800,500), "menuState");
    window.setFramerateLimit(60);

    //lettertype inladen
    sf::Font arialFont;
    if (!arialFont.loadFromFile("input_output/arial.ttf")) {
        std::cerr << "Kon het lettertype niet laden!" << std::endl;
    }

    // de pagina naam en de prev hisgh score afdrrukken
    sf::Text menuText = makeText(arialFont, "Menu", 60, sf::Color::Yellow, 320, 50);
    sf::Text highscoreText = makeText(arialFont, "Previous High score: " + std::to_string(prevHigh), 20, sf::Color::White, 280, 150);

    // de play butten
    sf::RectangleShape playButton(sf::Vector2f(300, 100));
    playButton.setFillColor(sf::Color::Green);
    playButton.setPosition(250, 250);

    sf::Text playText = makeText(arialFont, "Play", 60, sf::Color::Magenta, 320, 50);
    // Tekst centreren in de knop
    sf::FloatRect textRect = playText.getLocalBounds();
    playText.setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top + textRect.height / 2.0f);
    playText.setPosition(
        playButton.getPosition().x + playButton.getSize().x / 2.0f,
        playButton.getPosition().y + playButton.getSize().y / 2.0f
    );


    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (playButton.getGlobalBounds().contains(mousePos)) {
                    //TODO: zou de ander moeten oproepen
                    window.close();

                }
            }
        }
        window.clear(sf::Color::Black);
        window.draw(menuText);
        window.draw(highscoreText);
        window.draw(playButton);
        window.draw(playText);
        window.display();
    }
};

LevelState::LevelState() {
    sf::RenderWindow window(sf::VideoMode(300,300), "levelState");
    window.setFramerateLimit(60);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        window.display();
    }
};

