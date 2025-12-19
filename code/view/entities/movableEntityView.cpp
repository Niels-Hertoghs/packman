//
// Created by niels_hertoghs on 11/16/25.
//

#include "movableEntityView.h"
#include "../../logic/entities/movableEntity.h"
#include "../../logic/Stopwatch.h"

namespace view {
movableEntityView::movableEntityView(sf::RenderWindow& window, camera& cam, double x, double y,
                                     const std::vector<std::pair<int, int>>& SpriteCo, int _aantalSprites,
                                     const std::vector<std::vector<std::pair<int, int>>>& allSprites)
    : entityView(window, cam, x, y), aantalSprites(_aantalSprites), counter(0), allSprites(allSprites),
      originalAllSprites(allSprites), spriteCo(SpriteCo) {

    try {
        sf::Texture Texture;
        if (!Texture.loadFromFile("input_output/sprite.png")) {
            throw std::runtime_error("Texture file with name \"input_output/sprite.png\" does not exist");
        }
        texture = Texture;
    } catch (const std::exception& e) {
        throw std::runtime_error("Fout bij het openen of verwerken van bestand.");
    }

    int PacmanSizeHeight = cam.distanceToPixelsHeight(2.f / 14.f);
    int PacmanSizeWidth = cam.distanceToPixelsWidth(2.f / 20.f);
    sf::RectangleShape Movable(sf::Vector2f(static_cast<float>(PacmanSizeWidth), static_cast<float>(PacmanSizeHeight)));

    Movable.setTexture(&texture);
    Movable.setTextureRect(sf::IntRect(spriteCo[counter].first, spriteCo[counter].second, 46, 41));

    sf::FloatRect bounds = Movable.getLocalBounds();
    Movable.setOrigin(bounds.width / 2, bounds.height / 2);
    _movable = Movable;

    id = nextId++; // unieke id toewijzen

    std::pair<unsigned int, unsigned int> pos = cam.worldToPixel(x, y);
    _movable.setPosition(static_cast<float>(pos.first), static_cast<float>(pos.second));
}

void movableEntityView::draw() {
    _movable.setTextureRect(sf::IntRect(spriteCo[counter].first, spriteCo[counter].second, 46, 41));
    window.draw(_movable);

    if (logic::Stopwatch::getInstance()->changeSprite(id)) {
        counter = (counter + 1) % aantalSprites; // volgende sprite
    }

    const int MovableSizeHeight = _camera.distanceToPixelsHeight(2.f / 14.f);
    const int MovableSizeWidth = _camera.distanceToPixelsWidth(2.f / 20.f);
    _movable.setSize(sf::Vector2f(static_cast<float>(MovableSizeWidth), static_cast<float>(MovableSizeHeight)));

    std::pair<unsigned int, unsigned int> pos = _camera.worldToPixel(x, y);
    _movable.setPosition(static_cast<float>(pos.first), static_cast<float>(pos.second));

    const sf::FloatRect bounds = _movable.getLocalBounds();
    _movable.setOrigin(bounds.width / 2, bounds.height / 2);
}

void movableEntityView::notify(const logic::notifications& message) {
    switch (message.type) {
    case logic::notificationTypes::CHANGE_POSITION: {
        x = message.x;
        y = message.y;
        break;
    }
    case logic::notificationTypes::CHANGE_DIRECTION_DOWN: {
        spriteCo = allSprites[0];
        break;
    }
    case logic::notificationTypes::CHANGE_DIRECTION_UP: {
        spriteCo = allSprites[1];
        break;
    }
    case logic::notificationTypes::CHANGE_DIRECTION_RIGHT: {
        spriteCo = allSprites[2];
        break;
    }
    case logic::notificationTypes::CHANGE_DIRECTION_LEFT: {
        spriteCo = allSprites[3];
        break;
    }
    case logic::notificationTypes::TO_FEAR_MODE: {
        if (isGhost()) {
            allSprites = {{{-5, 550}, {-5, 600}}, {{-5, 550}, {-5, 600}}, {{-5, 550}, {-5, 600}},
                          {{-5, 550}, {-5, 600}}};
            spriteCo = {{-5, 550}, {-5, 600}};
        }
        break;
    }
    case logic::notificationTypes::TO_CHASING_MODE: {
        if (isGhost()) {
            allSprites = originalAllSprites;

        }
        break;
    }
    default:
        return;
    }
}


packmanView::packmanView(sf::RenderWindow& window, camera& cam, double x, double y)
    : movableEntityView(window, cam, x, y, {{847, 51}, {847, 101}, {847, 51}, {847, 1}}, 4,
                        {{{846, 201}, {846, 251}, {846, 201}, {846, 151}},
                         {{847, 500}, {847, 550}, {847, 500}, {847, 450}},
                         {{847, 51}, {847, 101}, {847, 51}, {847, 1}},
                         {{846, 351}, {846, 401}, {846, 351}, {846, 301}}}) {
}

bool packmanView::isGhost() {
    return false;
}

}
