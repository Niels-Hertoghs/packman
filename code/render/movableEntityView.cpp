//
// Created by niels_hertoghs on 11/16/25.
//

#include "movableEntityView.h"

#include <iostream>

#include "../logic/entities/movableEntity.h"

namespace view {
    movableEntityView::movableEntityView(Stopwatch& stopwatch, sf::RenderWindow& window, camera cam)
        : entityView(stopwatch, window, cam) {

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
        : movableEntityView(stopwatch, window, cam), pacmanModel(pacmanModel) {

        int PacmanSizeHeight =  cam.distanceToPixelsHeight(2.f/14.f);
        int PacmanSizeWidth = cam.distanceToPixelsWidth(2.f/20.f);
        sf::RectangleShape Packman(sf::Vector2f(static_cast<float>(PacmanSizeWidth),static_cast<float>(PacmanSizeHeight)));

        Packman.setTexture(&texture);
        Packman.setTextureRect(sf::IntRect(847, 51, 45, 41));

        sf::FloatRect bounds = Packman.getLocalBounds();
        Packman.setOrigin(bounds.width/2,bounds.height/2);

        std::pair<unsigned int,unsigned int> pos = cam.worldToPixel(pacmanModel->getX(),pacmanModel->getY());
        Packman.setPosition(pos.first,pos.second);
        _pacman = Packman;
    }

    void packmanView::draw() {
        window.draw(_pacman);
    }

    void packmanView::notify(enum notifications message) {
        // direction veranderen
    }



}
