//
// Created by niels on 10/30/25.
//
#include <SFML/Graphics.hpp>
#include <memory>
#include "stateManeger.h"
#include <fstream>

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
    std::pair<int,int> menuPos = cam.worldToPixel(0.f, 0.55f);
    sf::Text menuText = makeText(packmanFont, "Menu", 60, sf::Color::Yellow, menuPos.first, menuPos.second);
    sf::FloatRect menuBounds = menuText.getLocalBounds();
    menuText.setOrigin(menuBounds.width / 2.f, menuBounds.height / 2.f); // het midden van de tekst is de coo waar het staat

    // De high score tekst
    std::pair<int,int> highPos = cam.worldToPixel(0.f, 0.35f);
    sf::Text highscoreText = makeText(packmanFont, "Previous High scores:", 20, sf::Color::White, highPos.first, highPos.second);
    sf::FloatRect highScoreRect = highscoreText.getLocalBounds();
    highscoreText.setOrigin(highScoreRect.width / 2.f, highScoreRect.height / 2.f);

    //De high scores zelf
    //De string maken
    std::ifstream file("input_output/HighScores.txt"); // open het bestand met de high score
    if (!file) {
        std::cerr << "Kon bestand niet openen.\n";
    }
    std::string inhoud((std::istreambuf_iterator<char>(file)),
                   std::istreambuf_iterator<char>()); // lees alles

    std::string highScoreText = "1: ";
    int teller = 1;
    for (char c : inhoud) {
         if (c == ' ') {
             highScoreText += '\n' +std::to_string(teller) + ": ";
             teller++;
         }
        highScoreText.push_back(c);
    }

    std::pair<int,int> highNumbPos = cam.worldToPixel(0.f, 0.f);
    sf::Text highNumbText = makeText(packmanFont, highScoreText, 20, sf::Color::White, highNumbPos.first, highNumbPos.second);
    sf::FloatRect highNumbBounds = highNumbText.getLocalBounds();
    highNumbText.setOrigin(highNumbBounds.width / 2.f, highNumbBounds.height / 2.f); // het midden van de tekst is de coo waar het staat



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
    window.draw(highNumbText);
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

