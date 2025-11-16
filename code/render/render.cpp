//
// Created by niels on 11/5/25.
//

#include "render.h"

#include "../logic/entities/collectable.h"

sf::Text makeText2(const sf::Font& fontF, const std::string& text, double charSize, sf::Color color,double x, double y,const camera& cam) {
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

namespace render {
    Render::Render(const camera &cam, std::shared_ptr<Score> sc) : cam(cam), score(sc) {
        sf::Texture Texture;
        if (!Texture.loadFromFile("input_output/sprite.png")) {
            std::cerr << "Kon fruit texture niet laden!" << std::endl;
        }
        texture = Texture;
    }


    void Render::Leveltekst(const camera& camera, const sf::Font& fontF) {
        // level tekst maken
        int level = 1; //TODO: het huidige level opvragen
        sf::Text levelText = makeText2(fontF, "Level: " + std::to_string(level), 0.16f, sf::Color::Yellow, 0.f, 1.f - 1.f/7.f,cam);
        text.push_back(levelText);

        // Score afbeelden (links vanonder)
        // int currentScore = score->getScore();
        // sf::Text scoreText = makeText2(fontF, "SCORE: " + std::to_string(currentScore) , 0.05, sf::Color::Yellow, -0.95f, -0.95f, camera); //TODO: grote aanpassen + plaats
        // sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
        // scoreText.setOrigin(0,scoreTextBounds.height);
        // text.push_back(scoreText);


        // remainings lifes afbeelden (rechts vanonder)
        int remainingLifes = 3; //TODO: remaining lifes halen uit...
        sf::Text LifesText = makeText2(fontF, "# LIFES REMAINING:" + std::to_string(remainingLifes) , 0.05, sf::Color::Yellow, 0.95f, -0.95f, camera);
        sf::FloatRect LifesBounds = LifesText.getLocalBounds();
        LifesText.setOrigin(LifesBounds.width,LifesBounds.height);
        text.push_back(LifesText);
    }

    void Render::addWall(double x,double y) {
        // int WallSizeHeight = cam.distanceToPixelsHeight(2.f/14.f);
        // int WallSizeWidth = cam.distanceToPixelsWidth(2.f/20.f);
        // sf::RectangleShape wall(sf::Vector2f(static_cast<float>(WallSizeWidth),static_cast<float>(WallSizeHeight)));
        // wall.setFillColor(sf::Color::Blue);
        // std::pair<unsigned int,unsigned int> pos = cam.worldToPixel(x,y);
        // wall.setPosition(pos.first,pos.second);
        // wall.setOrigin(0,0);
        // sprites.push_back(wall);
    }

    void Render::addCoin(double x,double y) {
        // int radius = cam.distanceToPixelsHeight(0.016f);
        // sf::CircleShape coinShape(radius);
        // std::pair<unsigned int,unsigned int> pos = cam.worldToPixel(x,y);
        // coinShape.setPosition(pos.first,pos.second);
        // sf::FloatRect bounds = coinShape.getLocalBounds();
        // coinShape.setOrigin(bounds.width/2,bounds.height/2);
        // coinShape.setFillColor(sf::Color::White);
        // coins.push_back(coinShape);
    }

    void Render::addFruit(double x,double y) {
        // int FruitSizeHeight = cam.distanceToPixelsHeight(1.f/17.f);
        // int FruitSizeWidth = cam.distanceToPixelsWidth(1.f/27.f);
        // sf::RectangleShape Fruit(sf::Vector2f(static_cast<float>(FruitSizeWidth),static_cast<float>(FruitSizeHeight)));
        //
        // Fruit.setTexture(&texture);
        // Fruit.setTextureRect(sf::IntRect(601, 153, 36, 36));
        //
        // sf::FloatRect bounds = Fruit.getLocalBounds();
        // Fruit.setOrigin(bounds.width/2,bounds.height/2);
        //
        // std::pair<unsigned int,unsigned int> pos = cam.worldToPixel(x,y);
        // Fruit.setPosition(pos.first,pos.second);
        // sprites.push_back(Fruit);
    }

    void Render::addPackman(double x, double y) {
        // int PacmanSizeHeight =  cam.distanceToPixelsHeight(2.f/14.f);
        // int PacmanSizeWidth = cam.distanceToPixelsWidth(2.f/20.f);
        // sf::RectangleShape Packman(sf::Vector2f(static_cast<float>(PacmanSizeWidth),static_cast<float>(PacmanSizeHeight)));
        //
        // Packman.setTexture(&texture);
        // Packman.setTextureRect(sf::IntRect(847, 51, 45, 41));
        //
        // sf::FloatRect bounds = Packman.getLocalBounds();
        // Packman.setOrigin(bounds.width/2,bounds.height/2);
        //
        // std::pair<unsigned int,unsigned int> pos = cam.worldToPixel(x,y);
        // Packman.setPosition(pos.first,pos.second);
        // sprites.push_back(Packman);
    };
}