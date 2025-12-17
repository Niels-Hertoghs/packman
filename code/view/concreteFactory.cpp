//
// Created by niels-hertoghs on 12/12/25.
//
#include "../logic/entities/Ghost.h"
#include "../logic/entities/collectable.h"
#include "concreteFactory.h"

namespace view {
concreteFactory::concreteFactory(camera& camera, sf::RenderWindow& window, std::shared_ptr<worldView> wereld)
    : _camera(camera), window(window), worldV(std::move(wereld)) {
}

std::shared_ptr<logic::Ghost> concreteFactory::createGhost(const ghostTypes typeGhost, const double x, const double y, float speed, int points) {
    std::shared_ptr<logic::Ghost> ghost;
    std::shared_ptr<ghostView> ghostV;
    switch (typeGhost) {
    case ghostTypes::RED: {
        ghost = std::make_shared<logic::redGhost>(x + 1.f / 20.f, y - 1.f / 14.f, speed, points);
        ghostV = std::make_shared<redGhostView>(window, _camera, ghost->getX(), ghost->getY());
        break;
    }
    case ghostTypes::GREEN: {
        ghost = std::make_shared<logic::greenGhost>(x + 1.f / 20.f, y - 1.f / 14.f, speed, points);
        ghostV = std::make_shared<greenGhostView>(window, _camera, ghost->getX(), ghost->getY());
        break;
    }
    case ghostTypes::BLUE: {
        ghost = std::make_shared<logic::blueGhost>(x + 1.f / 20.f, y - 1.f / 14.f, speed, points);
        ghostV = std::make_shared<blueGhostView>(window, _camera, ghost->getX(), ghost->getY());
        break;
    }
    case ghostTypes::ORANGE: {
        ghost = std::make_shared<logic::orangeGhost>(x + 1.f / 20.f, y - 1.f / 14.f, speed, points);
        ghostV = std::make_shared<orangeGhostView>(window, _camera, ghost->getX(), ghost->getY());
        break;
    }
    default:
        break;
    }
    ghost->subscribe(ghostV);
    worldV->addGhostView(ghostV);
    return std::move(ghost);
}

std::shared_ptr<logic::Pacman> concreteFactory::createPacman (double x, double y, float speed) {
    std::shared_ptr<logic::Pacman> pacmanModel = std::make_shared<logic::Pacman>(x + 1.f / 20.f, y - 1.f / 14.f, speed);
    const std::shared_ptr<packmanView> PacmanView = std::make_shared<packmanView>(
        window, _camera, pacmanModel->getX(), pacmanModel->getY());
    pacmanModel->subscribe(PacmanView);
    worldV->addPacmanView(PacmanView);
    return std::move(pacmanModel);
}

std::shared_ptr<logic::wall> concreteFactory::createWall(double x, double y) {
    std::shared_ptr<logic::wall> wall = std::make_shared<logic::wall>(x, y);
    std::shared_ptr<wallView> wallV = std::make_shared<wallView>(window, _camera, wall->getX(), wall->getY());
    wall->subscribe(wallV);
    worldV->addWallView(wallV);
    return std::move(wall);
}

std::shared_ptr<logic::invisibleWall> concreteFactory::createInvisibleWall(double x, double y) {
    std::shared_ptr<logic::invisibleWall> wall = std::make_shared<logic::invisibleWall>(x, y);
    return std::move(wall);
}


std::shared_ptr<logic::collectable> concreteFactory::createCollectable(const collectableTypes typeCollectable,
                                                                    const double x,
                                                                    const double y, int points) {
    std::shared_ptr<logic::collectable> collectable;
    std::shared_ptr<collectableView> collectableView;
    switch (typeCollectable) {
    case collectableTypes::COIN: {
        collectable = std::make_shared<logic::coin>(x + 1.f / 20.f, y - 1.f / 14.f, points);
        collectableView = std::make_shared<coinView>(
    window, _camera, collectable->getX(), collectable->getY());
        break;
    }
    case collectableTypes::FRUIT: {
        collectable = std::make_shared<logic::fruit>(x + 1.f / 20.f, y - 1.f / 14.f, points);
        collectableView = std::make_shared<fruitView>(
            window, _camera, collectable->getX(), collectable->getY());
        break;
    }
    default:
        break;
    }
    collectable->subscribe(collectableView);
    worldV->addCollectableView(collectableView);
    return std::move(collectable);
}
} // view
