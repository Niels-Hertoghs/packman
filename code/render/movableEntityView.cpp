//
// Created by niels_hertoghs on 11/16/25.
//

#include "movableEntityView.h"

#include <iostream>

#include "../logic/entities/movableEntity.h"
int view::movableEntityView::nextId = 0;  // start bij 0

namespace view {
    movableEntityView::movableEntityView(Stopwatch& stopwatch, sf::RenderWindow& window, camera& cam,const std::vector<std::pair<int,int>>& SpriteCo, int _aantalSprites)
        : entityView(stopwatch, window, cam), spriteCo(SpriteCo), counter(0),aantalSprites(_aantalSprites),lastTimeChangedSprite(std::chrono::high_resolution_clock::now()) {

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

        int PacmanSizeHeight =  cam.distanceToPixelsHeight(2.f/14.f);
        int PacmanSizeWidth = cam.distanceToPixelsWidth(2.f/20.f);
        sf::RectangleShape Movable(sf::Vector2f(static_cast<float>(PacmanSizeWidth),static_cast<float>(PacmanSizeHeight)));

        Movable.setTexture(&texture);
        Movable.setTextureRect(sf::IntRect(spriteCo[counter].first,spriteCo[counter].second, 46, 41));

        sf::FloatRect bounds = Movable.getLocalBounds();
        Movable.setOrigin(bounds.width/2,bounds.height/2);
        _movable = Movable;

        id = nextId++;
    }

    void movableEntityView::draw() {
        _movable.setTextureRect(sf::IntRect(spriteCo[counter].first,spriteCo[counter].second, 46, 41));
        window.draw(_movable);

        if (stopwatch.changeSprite(id)) {
            counter = (counter + 1) % aantalSprites;  // volgende sprite
        }

        int MovableSizeHeight =  _camera.distanceToPixelsHeight(2.f/14.f);
        int MovableSizeWidth = _camera.distanceToPixelsWidth(2.f/20.f);
        _movable.setSize(sf::Vector2f(static_cast<float>(MovableSizeWidth),static_cast<float>(MovableSizeHeight)));
    }


    packmanView::packmanView(Stopwatch& stopwatch, sf::RenderWindow& window, camera& cam,std::shared_ptr<logic::Packman>& pacmanModel)
        : movableEntityView(stopwatch, window, cam,{{847,51},{847,101},{847,51},{847,1}},4), pacmanModel(pacmanModel) {

        std::pair<unsigned int,unsigned int> pos = cam.worldToPixel(pacmanModel->getX(),pacmanModel->getY());
        _movable.setPosition(pos.first,pos.second);
    }

    void packmanView::notify(enum notifications message) {
        if (message == notifications::CHANGE_POSITION) {
            std::pair<unsigned int,unsigned int> pos;
            if (auto observer = pacmanModel.lock()) {
                pos = _camera.worldToPixel(observer->getX(),observer->getY());
            }
            _movable.setPosition(pos.first,pos.second);
        } else if ( message == notifications::CHANGE_DIRECTION_DOWN) {
            spriteCo = {{846,201},{846,251},{846,201},{846,151}};
        } else if ( message == notifications::CHANGE_DIRECTION_UP) {
            spriteCo = {{847,500},{847,550},{847,500},{847,450}};
        } else if ( message == notifications::CHANGE_DIRECTION_RIGHT) {
            spriteCo = {{847,51},{847,101},{847,51},{847,1}};
        } else if ( message == notifications::CHANGE_DIRECTION_LEFT) {
            spriteCo = {{846,351},{846,401},{846,351},{846,301}};
        }
    }

}
