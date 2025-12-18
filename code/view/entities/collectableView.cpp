//
// Created by niels_hertoghs on 11/16/25.
//

#include "collectableView.h"

#include <iostream>

#include "../../logic/entities/collectable.h"

namespace view {
    collectableView::collectableView(sf::RenderWindow &window, camera &cam, double x, double y)
        : entityView(window, cam, x, y), collected(false) {
    }

    coinView::coinView(sf::RenderWindow &window, camera &cam, double x, double y)
        : collectableView(window, cam, x, y) {
        int radius = std::min(_camera.distanceToPixelsHeight(0.016f), _camera.distanceToPixelsWidth(0.016f));
        sf::CircleShape coinShape(static_cast<float>(radius));
        std::pair<unsigned int, unsigned int> pos = cam.worldToPixel(x, y);
        coinShape.setPosition(static_cast<float>(pos.first), static_cast<float>(pos.second));
        sf::FloatRect bounds = coinShape.getLocalBounds();
        coinShape.setOrigin(bounds.width / 2, bounds.height / 2);
        coinShape.setFillColor(sf::Color::White);
        _coin = coinShape;
    }

    void coinView::draw() {
        if (collected) {
            return;
        }
        std::pair<unsigned int, unsigned int> pos = _camera.worldToPixel(x, y);
        _coin.setRadius(static_cast<float>(std::min(_camera.distanceToPixelsHeight(0.016f),
                                                    _camera.distanceToPixelsWidth(0.016f))));
        _coin.setPosition(static_cast<float>(pos.first), static_cast<float>(pos.second));
        const sf::FloatRect bounds = _coin.getLocalBounds();
        _coin.setOrigin(bounds.width / 2, bounds.height / 2);
        window.draw(_coin);
    }

    void coinView::notify(const notifications &message) {
        if (message.type == notificationTypes::COLLECTED) {
            collected = true;
        }
    }


    fruitView::fruitView(sf::RenderWindow &window, camera &cam, double x, double y)
        : collectableView(window, cam, x, y) {
        try {
            sf::Texture Texture;
            if (!Texture.loadFromFile("input_output/sprite.png")) {
                throw std::runtime_error("Texture file with name \"input_output/sprite.png\" does not exist");
            }
            texture = Texture;
        } catch (const std::exception &e) {
            std::cerr << "Fout bij het openen of verwerken van bestand: " << e.what() << std::endl;
            throw;
        }

        int FruitSizeHeight = cam.distanceToPixelsHeight(1.f / 17.f);
        int FruitSizeWidth = cam.distanceToPixelsWidth(1.f / 27.f);
        sf::RectangleShape Fruit(sf::Vector2f(static_cast<float>(FruitSizeWidth), static_cast<float>(FruitSizeHeight)));

        Fruit.setTexture(&texture);
        Fruit.setTextureRect(sf::IntRect(601, 153, 36, 36));

        sf::FloatRect bounds = Fruit.getLocalBounds();
        Fruit.setOrigin(bounds.width / 2, bounds.height / 2);

        std::pair<unsigned int, unsigned int> pos = cam.worldToPixel(x, y);
        Fruit.setPosition(static_cast<float>(pos.first), static_cast<float>(pos.second));
        _fruit = Fruit;
    }

    void fruitView::draw() {
        if (collected) {
            return;
        }

        std::pair<unsigned int, unsigned int> pos = _camera.worldToPixel(x, y);
        const int FruitSizeHeight = _camera.distanceToPixelsHeight(1.f / 17.f);
        const int FruitSizeWidth = _camera.distanceToPixelsWidth(1.f / 27.f);
        _fruit.setSize(sf::Vector2f(static_cast<float>(FruitSizeWidth), static_cast<float>(FruitSizeHeight)));
        _fruit.setPosition(static_cast<float>(pos.first), static_cast<float>(pos.second));

        const sf::FloatRect bounds = _fruit.getLocalBounds();
        _fruit.setOrigin(bounds.width / 2, bounds.height / 2);

        window.draw(_fruit);
    }

    void fruitView::notify(const notifications &message) {
        if (message.type == notificationTypes::COLLECTED) {
            collected = true;
        }
    }
}