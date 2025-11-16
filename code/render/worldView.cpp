//
// Created by niels_hertoghs on 11/13/25.
//

#include "worldView.h"
#include "../world.h"

namespace view {
    worldView::worldView(const std::shared_ptr<logic::world>& wereld,Stopwatch& stopwatch, camera camera, sf::RenderWindow& window) {
        for (std::shared_ptr<logic::wall>& _wall : wereld->get_walls()) {
            std::shared_ptr<wallView> wall = std::make_shared<wallView>(stopwatch,window,camera,_wall);
            _wall->wallSubscribe(wall);
            walls.push_back(wall);
        }

        std::shared_ptr<logic::Packman> Pacman = wereld->get_pacman();
        std::shared_ptr<packmanView> PacmanView = std::make_shared<packmanView>(stopwatch,window,camera,Pacman);
        Pacman->pacmanSubscribe(PacmanView);
        pacman = PacmanView;
    }

    void worldView::draw() {
        for (std::shared_ptr<view::wallView>& muur : walls) {
            muur->draw();
        }
        pacman->draw();
    }
}