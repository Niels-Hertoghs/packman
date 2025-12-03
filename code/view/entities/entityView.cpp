//
// Created by niels_hertoghs on 11/13/25.
//

#include "entityView.h"
#include <utility>


namespace view {
    entityView::entityView(sf::RenderWindow& window,camera& cam) : Observer(window,cam) {
    }

    wallView::wallView(sf::RenderWindow& window, camera& cam, std::shared_ptr<logic::wall>& wallM)
    : entityView(window,cam),wallModel(wallM) {

        int WallSizeHeight = _camera.distanceToPixelsHeight(2.f/14.f);
        int WallSizeWidth = _camera.distanceToPixelsWidth(2.f/20.f);
        sf::RectangleShape wall(sf::Vector2f(static_cast<float>(WallSizeWidth),static_cast<float>(WallSizeHeight)));
        _wall = wall;
        _wall.setFillColor(sf::Color::Blue);
        std::pair<unsigned int,unsigned int> pos = cam.worldToPixel(wallM->getX(),wallM->getY());
        _wall.setPosition(static_cast<float>(pos.first),static_cast<float>(pos.second));
        _wall.setOrigin(0,0); // = links boven hoek
    }


    void wallView::draw() {
        std::pair<unsigned int,unsigned int> pos;
        if (const auto observer = wallModel.lock()) {
            pos = _camera.worldToPixel(observer->getX(),observer->getY());
        }
        const int WallSizeHeight = _camera.distanceToPixelsHeight(2.f/14.f);
        const int WallSizeWidth = _camera.distanceToPixelsWidth(2.f/20.f);
        _wall.setSize(sf::Vector2f(static_cast<float>(WallSizeWidth),static_cast<float>(WallSizeHeight)));
        _wall.setPosition(static_cast<float>(pos.first),static_cast<float>(pos.second));
        window.draw(_wall);
    }

    void wallView::notify(enum notifications message) {}
}