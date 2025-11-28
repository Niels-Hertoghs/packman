//
// Created by niels_hertoghs on 11/13/25.
//

#ifndef PACKMAN_WORLDVIEW_H
#define PACKMAN_WORLDVIEW_H
#include <memory>

#include "../observer.h"
#include "entityView.h"
#include "movableEntityView.h"
#include "collectableView.h"
#include "ghostView.h"
#include "ScoreView.h"

namespace logic {
    class world;
}

namespace view {
    // dit is voor als er objecten worden verwijderd dan doet die hier iets, bij de notify
    // anderws geeft die de melding door denk ik
    class worldView : public IObserver {
    private:
        std::vector<std::shared_ptr<wallView>> walls;
        std::vector<std::shared_ptr<fruitView>> fruits;
        std::vector<std::shared_ptr<coinView>> coins;
        // std::vector<std::shared_ptr<view::movableEntityView>> movables;
        std::shared_ptr<view::packmanView> pacman;

        std::shared_ptr<view::redGhostView> redGhost;
        std::shared_ptr<view::blueGhostView> blueGhost;
        std::shared_ptr<view::greenGhostView> greenGhost;
        std::shared_ptr<view::orangeGhostView> orangeGhost;


        std::shared_ptr<view::ScoreView> score;
    public:
        worldView(const std::shared_ptr<logic::world>& _wereld,camera& camera, sf::RenderWindow& window,std::shared_ptr<logic::Score>& score);
        void draw();
    };
}

#endif //PACKMAN_WORLDVIEW_H