//
// Created by niels_hertoghs on 11/10/25.
//

#include "observer.h"

#include <iostream>

class camera;

sf::Text makeText3(const sf::Font& fontF, const std::string& text, double charSize, sf::Color color,double x, double y,const camera& cam) {
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

Observer::Observer(sf::RenderWindow& window2,camera& cam)
    : window(window2), _camera(cam) {}

Score::Score(sf::RenderWindow& window,camera& cam) : Observer(window,cam), score(0) {}

void Score::coinEaten(float coinPoints) {
    float lastEatenTime = Stopwatch::getInstance().eatCollectable();
    // aantal coin points komt er bij de score als de collectable gegeten wordt na 1 sec
    // als het sneller wordt gedaan komen er meer punten bij, afhankelijk van hoe snel
    // (0.5 sec -> points verdubbeld, na 2 sec points gehalveerd)
    score += coinPoints/lastEatenTime;
}

int Score::getScore() const {
    return score;
}

void Score::draw() {
    sf::Font Font;
    if (!Font.loadFromFile("input_output/packman_font.ttf")) {
        std::cerr << "Kon het lettertype niet laden!" << std::endl;
    }

    // de score afbeelden
    int currentScore = score;
    sf::Text scoreText = makeText3(Font, "SCORE: " + std::to_string(currentScore) , 0.05, sf::Color::Yellow, -0.95f, -0.95f, _camera); //TODO: grote aanpassen + plaats
    sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setOrigin(0,scoreTextBounds.height);
    window.draw(scoreText);

    // het level afbeelden
    int level = 1; //TODO: het huidige level opvragen
    sf::Text levelText = makeText3(Font, "Level: " + std::to_string(level), 0.16f, sf::Color::Yellow, 0.f, 1.f - 1.f/7.f,_camera);
    window.draw(levelText);

    // remainings lifes afbeelden (rechts vanonder)
    int remainingLifes = 3; //TODO: remaining lifes halen uit...
    sf::Text LifesText = makeText3(Font, "# LIFES REMAINING:" + std::to_string(remainingLifes) , 0.05, sf::Color::Yellow, 0.95f, -0.95f, _camera);
    sf::FloatRect LifesBounds = LifesText.getLocalBounds();
    LifesText.setOrigin(LifesBounds.width,LifesBounds.height);
    window.draw(LifesText);
}

void Score::notify(enum notifications message) {
    std::cout << message << std::endl;
}




