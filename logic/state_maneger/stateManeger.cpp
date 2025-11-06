//
// Created by niels on 10/30/25.
//
#include <SFML/Graphics.hpp>
#include <memory>
#include "stateManeger.h"
#include <fstream>

#include "../render.h"
#include "../world.h"

sf::Text makeText(const sf::Font& fontF, const std::string& text, float charSize, sf::Color color,float x, float y,const camera& cam) {
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

void stateManeger::runTop(sf::RenderWindow& window, sf::Event& event, const camera& cam,world& wereld) {
    stack.top().get()->run(window, event,*this,cam,wereld);
}


// menu state
void menuState::run(sf::RenderWindow& window, sf::Event& event,stateManeger& manager, const camera& cam,world& wereld) {

    //lettertype inladen
    sf::Font packmanFont;
    if (!packmanFont.loadFromFile("input_output/packman_font.ttf")) {
        std::cerr << "Kon het lettertype niet laden!" << std::endl;
    }

    // menu title maken
    sf::Text menuText = makeText(packmanFont, "Menu", 0.15f, sf::Color::Yellow, 0.f, 0.55f,cam);

    // De high score tekst
    sf::Text highscoreText = makeText(packmanFont, "Previous High scores:", 0.1f, sf::Color::White, 0.f, 0.35f,cam);


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
    int playButtenSizeHeight = cam.distanceToPixelsHeight(0.4f);
    int playButtenSizeWidth = cam.distanceToPixelsWidth(1.2f);
    sf::RectangleShape playButton(sf::Vector2f(static_cast<float>(playButtenSizeWidth),static_cast<float>(playButtenSizeHeight)));
    playButton.setFillColor(sf::Color::Green);
    sf::FloatRect boundsRect =  playButton.getLocalBounds();
    playButton.setOrigin(boundsRect.width / 2.f, boundsRect.height / 2.f);
    std::pair<int, int> playButtenPos = cam.worldToPixel(0.f,-0.5f);
    playButton.setPosition(static_cast<float>(playButtenPos.first), static_cast<float>(playButtenPos.second));

    sf::Text playText = makeText(packmanFont, "Play", 0.2f, sf::Color::Magenta, 0.f, -0.5f,cam);

    if (event.type == sf::Event::MouseButtonPressed &&
         event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (playButton.getGlobalBounds().contains(mousePos)) {
            manager.pushState(std::make_unique<LevelState>());
        }
    }

    // alles tekenen op de window
    window.draw(menuText);
    window.draw(highNumbText);
    window.draw(highscoreText);
    window.draw(playButton);
    window.draw(playText);
}

void LevelState::run(sf::RenderWindow &window, sf::Event &event, stateManeger &manager, const camera& cam,world& wereld) {
    // Render render;

    sf::Font Font;
    if (!Font.loadFromFile("input_output/packman_font.ttf")) {
        std::cerr << "Kon het lettertype niet laden!" << std::endl;
    }

    // alle sprites in een render classe zetten
    Render* tussen = wereld.render(cam,Font);

    // alle sprites in de window zetten
    for (const auto& line:tussen->sprites) {
        window.draw(line);
    }

    // alle coins in de window zetten
    for (const auto& line:tussen->coins) {
        window.draw(line);
    }

    // alle text in de window zetten
    for (const auto& text:tussen->text) {
        window.draw(text);
    }
}

