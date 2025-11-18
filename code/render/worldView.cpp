//
// Created by niels_hertoghs on 11/13/25.
//

#include "worldView.h"
#include "../world.h"

namespace view {
    worldView::worldView(const std::shared_ptr<logic::world>& wereld,Stopwatch& _stopwatch, camera& camera, sf::RenderWindow& window,std::shared_ptr<Score>& _score)
        : score(_score)
    {

        // De wall observers worden aangemaakt en gelinkt aan de models.
        for (std::shared_ptr<logic::wall>& _wall : wereld->get_walls()) {
            std::shared_ptr<wallView> wall = std::make_shared<wallView>(_stopwatch,window,camera,_wall);
            _wall->wallSubscribe(wall);
            walls.push_back(wall);
        }

        // De fruit observers worden aangemaakt en gelinkt aan de models.
        for (std::shared_ptr<logic::fruit>& _fruit : wereld->get_fruits()) {
            std::shared_ptr<fruitView> fruit = std::make_shared<fruitView>(_stopwatch,window,camera,_fruit);
            _fruit->fruitSubscribe(fruit);
            fruits.push_back(fruit);
        }

        // De wall observers worden aangemaakt en gelinkt aan de models.
        for (std::shared_ptr<logic::coin>& _coin : wereld->get_coins()) {
            std::shared_ptr<coinView> coin = std::make_shared<coinView>(_stopwatch,window,camera,_coin);
            _coin->coinSubscribe(coin);
            coins.push_back(coin);
        }

        // pacman observer wordt aangemaakt en gelinkt aan pacman model.
        std::shared_ptr<logic::Packman> Pacman = wereld->get_pacman();
        std::shared_ptr<packmanView> PacmanView = std::make_shared<packmanView>(_stopwatch,window,camera,Pacman);
        Pacman->pacmanSubscribe(PacmanView);
        pacman = PacmanView;

        std::shared_ptr<logic::redGhost> red_ghost = wereld->get_red_ghost();
        std::shared_ptr<redGhostView> _redGhostView = std::make_shared<redGhostView>(_stopwatch,window,camera,red_ghost);
        red_ghost->redGhostSubscribe(_redGhostView);
        redGhost = _redGhostView;
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
        score->draw();
    }
}