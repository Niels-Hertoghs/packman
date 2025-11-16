//
// Created by niels_hertoghs on 11/16/25.
//

#include "movableEntityView.h"

#include <iostream>

#include "../logic/entities/movableEntity.h"

namespace view {
    movableEntityView::movableEntityView(Stopwatch& stopwatch, sf::RenderWindow& window, camera cam,const std::vector<std::pair<int,int>>& SpriteCo)
        : entityView(stopwatch, window, cam), spriteCo(SpriteCo), counter(0) {

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
    }

    packmanView::packmanView(Stopwatch& stopwatch, sf::RenderWindow& window, camera cam,std::shared_ptr<logic::Packman>& pacmanModel)
        : movableEntityView(stopwatch, window, cam,{{847,51},{847,101},{847,51},{847,1}}), pacmanModel(pacmanModel) {

        int PacmanSizeHeight =  cam.distanceToPixelsHeight(2.f/14.f);
        int PacmanSizeWidth = cam.distanceToPixelsWidth(2.f/20.f);
        sf::RectangleShape Packman(sf::Vector2f(static_cast<float>(PacmanSizeWidth),static_cast<float>(PacmanSizeHeight)));

        Packman.setTexture(&texture);
        Packman.setTextureRect(sf::IntRect(847, 51, 46, 41));

        sf::FloatRect bounds = Packman.getLocalBounds();
        Packman.setOrigin(bounds.width/2,bounds.height/2);

        std::pair<unsigned int,unsigned int> pos = cam.worldToPixel(pacmanModel->getX(),pacmanModel->getY());
        Packman.setPosition(pos.first,pos.second);
        _pacman = Packman;
    }

    void packmanView::draw() {
        _pacman.setTextureRect(sf::IntRect(spriteCo[counter].first,spriteCo[counter].second, 46, 41));
        window.draw(_pacman);

        if (stopwatch.changeSprite()) {
            counter = (counter + 1) % 4;  // volgende sprite
        }
    }

    void packmanView::notify(enum notifications message) {
        if (message == notifications::CHANGE_POSITION) {
            std::pair<unsigned int,unsigned int> pos;
            if (auto observer = pacmanModel.lock()) {
                pos = _camera.worldToPixel(observer->getX(),observer->getY());
            }
            _pacman.setPosition(pos.first,pos.second);
        } else if ( message == notifications::CHANGE_DIRECTION_DOWN) {
            spriteCo = {{846,201},{846,251},{846,201},{846,151}};
            counter = 0;
        } else if ( message == notifications::CHANGE_DIRECTION_UP) {
            spriteCo = {{847,500},{847,550},{847,500},{847,450}};
            counter = 0;
        } else if ( message == notifications::CHANGE_DIRECTION_RIGHT) {
            spriteCo = {{847,51},{847,101},{847,51},{847,1}};
            counter = 0;
        } else if ( message == notifications::CHANGE_DIRECTION_LEFT) {
            spriteCo = {{846,351},{846,401},{846,351},{846,301}};
            counter = 0;
        }
    }



}
