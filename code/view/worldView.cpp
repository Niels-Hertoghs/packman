//
// Created by niels_hertoghs on 11/13/25.
//

#include "worldView.h"
#include "../logic/world.h"
#include "ViewFactory.h"

namespace view {
worldView::worldView(const std::shared_ptr<logic::world>& wereld, camera& camera, sf::RenderWindow& window,
                     std::shared_ptr<logic::Score>& _score) {
    std::unique_ptr<ConcreteViewFactory> factory = std::make_unique<ConcreteViewFactory>(camera, window);

    // De wall observers worden aangemaakt en gelinkt aan de models.
    for (std::shared_ptr<logic::wall>& _wall : wereld->get_walls()) {
        walls.push_back(factory->createWallView(_wall));
    }

    // De fruit observers worden aangemaakt en gelinkt aan de models.
    for (std::shared_ptr<logic::collectable>& _collectable : wereld->get_collectables()) {
        collectables.push_back(factory->createCollectableView(_collectable));
    }

    for (const std::shared_ptr<logic::Ghost>& ghost : wereld->get_ghosts()) {
        ghosts.push_back(factory->createGhostView(ghost));
    }

    // pacman observer wordt aangemaakt en gelinkt aan pacman model.
    std::shared_ptr<logic::Pacman> Pacman = wereld->get_pacman();
    pacman = factory->createPacmanView(Pacman);

    std::shared_ptr<ScoreView> score_view = std::make_shared<ScoreView>(window, camera, _score);
    _score->subscribeScore(score_view);
    score = score_view;
}

void worldView::notify(const notifications& message) {

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
}
