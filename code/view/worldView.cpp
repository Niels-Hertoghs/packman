//
// Created by niels_hertoghs on 11/13/25.
//

#include "worldView.h"
#include "../world.h"

namespace view {
    worldView::worldView(const std::shared_ptr<logic::world>& wereld,camera& camera, sf::RenderWindow& window,std::shared_ptr<logic::Score>& _score)

    {

        // De wall observers worden aangemaakt en gelinkt aan de models.
        for (std::shared_ptr<logic::wall>& _wall : wereld->get_walls()) {
            std::shared_ptr<wallView> wall = std::make_shared<wallView>(window,camera,_wall);
            _wall->wallSubscribe(wall);
            walls.push_back(wall);
        }

        // De fruit observers worden aangemaakt en gelinkt aan de models.
        for (std::shared_ptr<logic::collectable>& _collectable : wereld->get_collectables()) {
            if (_collectable->isFruit()) {
                std::shared_ptr<fruitView> fruit = std::make_shared<fruitView>(window,camera,_collectable);
                _collectable->collectableSubscribe(fruit);
                fruits.push_back(fruit);
            } else {
                std::shared_ptr<coinView> coin = std::make_shared<coinView>(window,camera,_collectable);
                _collectable->collectableSubscribe(coin);
                coins.push_back(coin);
            }

        }


        // pacman observer wordt aangemaakt en gelinkt aan pacman model.
        std::shared_ptr<logic::Packman> Pacman = wereld->get_pacman();
        std::shared_ptr<packmanView> PacmanView = std::make_shared<packmanView>(window,camera,Pacman);
        Pacman->pacmanSubscribe(PacmanView);
        pacman = PacmanView;

        std::shared_ptr<logic::redGhost> red_ghost = wereld->get_red_ghost();
        std::shared_ptr<redGhostView> _redGhostView = std::make_shared<redGhostView>(window,camera,red_ghost);
        red_ghost->redGhostSubscribe(_redGhostView);
        redGhost = _redGhostView;

        std::shared_ptr<logic::blueGhost> blue_ghost = wereld->get_blue_ghost();
        std::shared_ptr<blueGhostView> _blueGhostView = std::make_shared<blueGhostView>(window,camera,blue_ghost);
        blue_ghost->blueGhostSubscribe(_blueGhostView);
        blueGhost = _blueGhostView;

        std::shared_ptr<logic::greenGhost> green_ghost = wereld->get_green_ghost();
        std::shared_ptr<greenGhostView> _greenGhostView = std::make_shared<greenGhostView>(window,camera,green_ghost);
        green_ghost->greenGhostSubscribe(_greenGhostView);
        greenGhost = _greenGhostView;

        std::shared_ptr<logic::orangeGhost> purple_ghost = wereld->get_orange_ghost();
        std::shared_ptr<orangeGhostView> _orangeGhostView = std::make_shared<orangeGhostView>(window,camera,purple_ghost);
        purple_ghost->orangeGhostSubscribe(_orangeGhostView);
        orangeGhost = _orangeGhostView;

        std::shared_ptr<ScoreView> score_view = std::make_shared<ScoreView>(window,camera,_score);
        _score->subscribeScore(score_view);
        score = score_view;
    }

    void worldView::draw() {
        for (std::shared_ptr<view::wallView>& muur : walls) {
            muur->draw();
        }
        for (std::shared_ptr<view::fruitView>& fruit : fruits) {
            fruit->draw();
        }
        for (std::shared_ptr<view::coinView>& coin : coins) {
            coin->draw();
        }
        pacman->draw();

        redGhost->draw();
        greenGhost->draw();
        orangeGhost->draw();
        blueGhost->draw();

        score->draw();
    }
}