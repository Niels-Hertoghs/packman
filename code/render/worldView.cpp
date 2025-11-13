//
// Created by niels_hertoghs on 11/13/25.
//

#include "worldView.h"

worldView::worldView(logic::world& wereld) {
    for (std::shared_ptr<logic::wall> w : wereld.get_walls()) {
        std::shared_ptr<wallView> wv;
        this->walls.push_back(wv);
        w->wallSubscribe(wv);
    }
}

void worldView::draw() {
    for (auto& muur : walls) {
        muur->draw();
    }
}
