//
// Created by niels_hertoghs on 11/13/25.
//

#include "worldView.h"
#include "../world.h"


worldView::worldView(const std::shared_ptr<logic::world>& wereld,Stopwatch& stopwatch, camera camera, sf::RenderWindow& window) {
    for (std::shared_ptr<logic::wall>& _wall : wereld->get_walls()) {
        std::shared_ptr<wallView> wall = std::make_shared<wallView>(stopwatch,window,camera,_wall);
        _wall->wallSubscribe(wall);
        walls.push_back(wall);
    }
}

void worldView::draw() {
    for (auto& muur : walls) {
        muur->draw();
    }
}
