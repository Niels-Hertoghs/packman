//
// Created by niels on 10/30/25.
//
#include <SFML/Graphics.hpp>
#include <memory>
#include "stateManeger.h"
#include <fstream>

sf::Text makeText(const sf::Font& fontF, const std::string& text, float charSize, sf::Color color,float x, float y,const camera& cam) {
    sf::Text Text;
    Text.setFont(fontF);
    Text.setString(text);
    Text.setCharacterSize(cam.distanceToPixelsHeight(charSize));
    Text.setFillColor(color);

    // Zet origin wél met top en left in aanmerking genomen
    sf::FloatRect bounds = Text.getLocalBounds();
    Text.setOrigin(bounds.left + bounds.width / 2.f,
                   bounds.top  + bounds.height / 2.f);

    // En pas dan pas de positie toe (zodat position refereert aan de nieuwe origin)
    auto Pos = cam.worldToPixel(x, y);
    Text.setPosition(static_cast<float>(Pos.first), static_cast<float>(Pos.second));

    return Text;
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
    sf::Text menuText = makeText(packmanFont, "Menu", 0.15, sf::Color::Yellow, 0.f, 0.55f,cam);
    sf::FloatRect menuBounds = menuText.getLocalBounds();
    // menuText.setOrigin(menuBounds.left + menuBounds.width / 2.f, menuBounds.height / 2.f); // het midden van de tekst is de coo waar het staat

    // De high score tekst
    sf::Text highscoreText = makeText(packmanFont, "Previous High scores:", 0.1f, sf::Color::White, 0.f, 0.35f,cam);
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
             highScoreText += '\n' +std::to_string(teller) + ":";
             teller++;
         }
        highScoreText.push_back(c);
    }

    sf::Text highNumbText = makeText(packmanFont, highScoreText, 0.05f, sf::Color::White, 0.f, 0.f,cam);
    sf::FloatRect highNumbBounds = highNumbText.getLocalBounds();
    highNumbText.setOrigin(highNumbBounds.width / 2.f, highNumbBounds.height / 2.f); // het midden van de tekst is de coo waar het staat



    //de play butten
    sf::RectangleShape playButton(sf::Vector2f(300, 100));
    playButton.setFillColor(sf::Color::Green);
    playButton.setPosition(250, 250);

    sf::Text playText = makeText(packmanFont, "Play", 0.2f, sf::Color::Magenta, -1.f, -1.f,cam);
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
    sf::Text menuText = makeText(arialFont, "Menu", 0.6, sf::Color::Yellow, 0.0f, 0.f,cam);
    window.draw(menuText);

}

