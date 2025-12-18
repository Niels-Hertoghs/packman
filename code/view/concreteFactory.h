//
// Created by niels-hertoghs on 12/12/25.
//

#ifndef PACKMAN_VIEWFACTORY_H
#define PACKMAN_VIEWFACTORY_H

#include "LogicFactory.h"
#include "entities/collectableView.h"
#include "entities/ghostView.h"
#include "entities/movableEntityView.h"
#include "worldView.h"
#include <memory>

namespace view {
class concreteFactory final : public logic::abstractFactory {
    camera& _camera;
    sf::RenderWindow& window;
    std::shared_ptr<worldView> worldV;

public:
    concreteFactory(camera& camera, sf::RenderWindow& window, std::shared_ptr<worldView> wereld);

    // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
    std::shared_ptr<logic::Pacman> createPacman(double x, double y, float speed) override;

    std::shared_ptr<logic::Ghost>
    createGhost(ghostTypes typeGhost, double x, double y, float speed, int points) override;

    std::shared_ptr<logic::wall> createWall(double x, double y) override;

    std::shared_ptr<logic::invisibleWall> createInvisibleWall(double x, double y) override;

    std::shared_ptr<logic::collectable> createCollectable(collectableTypes typeCollectable, double x, double y,
                                                          int points) override;
};
} // view

#endif //PACKMAN_VIEWFACTORY_H
