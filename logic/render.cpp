//
// Created by niels on 11/5/25.
//

#include "render.h"

sf::Text makeText2(const sf::Font& fontF, const std::string& text, float charSize, sf::Color color,float x, float y,const camera& cam) {
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

Render::Render() = default;

std::pair<std::vector<sf::RectangleShape>,std::vector<sf::Text>> Render::loadMap(const camera& camera, const sf::Font& fontF) {
    std::vector<sf::RectangleShape> rectangles;
    std::vector<sf::Text> text;

    // Score afbeelden (links vanonder)
    int currentScore = 100; //TODO: score halen uit score klasse
    sf::Text scoreText = makeText2(fontF, "SCORE: " + std::to_string(currentScore) , 0.05, sf::Color::Yellow, -0.95f, -0.95f, camera); //TODO: grote aanpassen + plaats
    sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setOrigin(0,scoreTextBounds.height);
    text.push_back(scoreText);


    // remainings lifes afbeelden (rechts vanonder)
    int remainingLifes = 3; //TODO: remaining lifes halen uit...
    sf::Text LifesText = makeText2(fontF, "# LIFES REMAINING:" + std::to_string(remainingLifes) , 0.05, sf::Color::Yellow, 0.95f, -0.95f, camera);
    sf::FloatRect LifesBounds = LifesText.getLocalBounds();
    LifesText.setOrigin(LifesBounds.width,LifesBounds.height);
    text.push_back(LifesText);

    return {rectangles,text};
}
