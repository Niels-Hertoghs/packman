//
// Created by niels_hertoghs on 11/13/25.
//

#include "worldView.h"
#include "../logic/world.h"
#include "concreteFactory.h"

namespace view {
worldView::worldView(const std::shared_ptr<logic::world>& wereld, camera& camera, sf::RenderWindow& window,
                     std::shared_ptr<logic::Score>& _score) {

    std::shared_ptr<ScoreView> score_view = std::make_shared<ScoreView>(window, camera, _score->getScore(),
                                                                        _score->getLevel(), _score->getLivesLeft());
    _score->subscribe(score_view);
    score = score_view;
}


void worldView::draw() const {
    for (const std::shared_ptr<view::wallView>& muur : walls) {
        muur->draw();
    }
    for (const std::shared_ptr<view::collectableView>& fruit : collectables) {
        fruit->draw();
    }

    pacman->draw();

    for (const std::shared_ptr<view::ghostView>& ghost : ghosts) {
        ghost->draw();
    }

    score->draw();
}

void worldView::addCollectableView(const std::shared_ptr<collectableView>& collectableV) {
    collectables.push_back(collectableV);
}

void worldView::addGhostView(const std::shared_ptr<ghostView>& ghostV) {
    ghosts.push_back(ghostV);
}

void worldView::addWallView(const std::shared_ptr<wallView>& wallV) {
    walls.push_back(wallV);
}

void worldView::addPacmanView(const std::shared_ptr<packmanView>& pacmanV) {
    pacman = pacmanV;
}

}
