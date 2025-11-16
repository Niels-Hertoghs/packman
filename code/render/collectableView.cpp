//
// Created by niels_hertoghs on 11/16/25.
//

#include "collectableView.h"

#include <iostream>

#include "../logic/entities/collectable.h"

namespace view {
    collectableView::collectableView(Stopwatch& stopwatch, sf::RenderWindow& window, camera cam)
        : entityView(stopwatch, window, cam),collected(false) {}

    coinView::coinView(Stopwatch& stopwatch, sf::RenderWindow& window, camera cam, std::shared_ptr<logic::coin>& CoinModel)
        : collectableView(stopwatch, window, cam), coinModel(CoinModel)

    {
        int radius = cam.distanceToPixelsHeight(0.016f);
        sf::CircleShape coinShape(radius);
        std::pair<unsigned int,unsigned int> pos = cam.worldToPixel(coinModel->getX(),coinModel->getY());
        coinShape.setPosition(pos.first,pos.second);
        sf::FloatRect bounds = coinShape.getLocalBounds();
        coinShape.setOrigin(bounds.width/2,bounds.height/2);
        coinShape.setFillColor(sf::Color::White);
        _coin = coinShape;
    }

    void coinView::draw() {
        if (!collected) {
            window.draw(_coin);
        }
    }

    void coinView::notify(enum notifications message) {
        if (message == notifications::COLLECTED) {
            collected = true;
            coinModel.reset();
        }

    }


    fruitView::fruitView(Stopwatch& stopwatch, sf::RenderWindow& window, camera cam, std::shared_ptr<logic::fruit>& FruitModel)
        : collectableView(stopwatch, window, cam), fruitModel(FruitModel)

    {
        try {
            sf::Texture Texture;
            if (!Texture.loadFromFile("input_output/sprite.png")) {
                throw std::runtime_error("Texture file with name \"input_output/sprite.png\" does not exist");
            }
            texture = Texture;
        } catch (const std::exception& e) {
            std::cerr << "Fout bij het openen of verwerken van bestand: " << e.what() << std::endl;
            throw;
        }

        int FruitSizeHeight = cam.distanceToPixelsHeight(1.f/17.f);
        int FruitSizeWidth = cam.distanceToPixelsWidth(1.f/27.f);
        sf::RectangleShape Fruit(sf::Vector2f(static_cast<float>(FruitSizeWidth),static_cast<float>(FruitSizeHeight)));

        Fruit.setTexture(&texture);
        Fruit.setTextureRect(sf::IntRect(601, 153, 36, 36));

        sf::FloatRect bounds = Fruit.getLocalBounds();
        Fruit.setOrigin(bounds.width/2,bounds.height/2);

        std::pair<unsigned int,unsigned int> pos = cam.worldToPixel(fruitModel->getX(),fruitModel->getY());
        Fruit.setPosition(pos.first,pos.second);
        _fruit = Fruit;
    }

    void fruitView::draw() {
        if (!collected) {
            window.draw(_fruit);
        }
    }

    void fruitView::notify(enum notifications message) {
        if (message == notifications::COLLECTED) {
            collected = true;
            fruitModel.reset();
        }

    }


}


