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


void Render::loadMap(const camera& camera, const sf::Font& fontF) {

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
}

void Render::addWall(float x,float y) {
    int WallSizeHeight = cam.distanceToPixelsHeight(2.f/14.f);
    int WallSizeWidth = cam.distanceToPixelsWidth(2.f/20.f);
    sf::RectangleShape wall(sf::Vector2f(static_cast<float>(WallSizeHeight),static_cast<float>(WallSizeWidth)));
    wall.setFillColor(sf::Color::Blue);
    std::pair<unsigned int,unsigned int> pair = cam.worldToPixel(x,y);
    wall.setPosition(pair.first,pair.second);
    wall.setOrigin(0,0);
    sprites.push_back(wall);
}
