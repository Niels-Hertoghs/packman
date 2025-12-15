//
// Created by niels-hertoghs on 12/12/25.
//
#include "../logic/entities/Ghost.h"
#include "../logic/entities/collectable.h"
#include "ViewFactory.h"


namespace view {
ConcreteViewFactory::ConcreteViewFactory(camera& camera, sf::RenderWindow& window)
    : _camera(camera), window(window) {
}

std::shared_ptr<ghostView> ConcreteViewFactory::createGhostView(std::shared_ptr<logic::Ghost> Model) {

    switch (ghostTypes type = Model->getType()) {
    case ghostTypes::RED: {
        std::shared_ptr<ghostView> Ghost = std::make_shared<redGhostView>(window, _camera, Model->getX(),Model->getY());
        Model->subscribe(Ghost);
        return Ghost;
    }
    case ghostTypes::GREEN: {
        std::shared_ptr<greenGhostView> Ghost = std::make_shared<greenGhostView>(window, _camera, Model->getX(),Model->getY());
        Model->subscribe(Ghost);
        return Ghost;
    }
    case ghostTypes::BLUE: {
        std::shared_ptr<blueGhostView> Ghost = std::make_shared<blueGhostView>(window, _camera, Model->getX(),Model->getY());
        Model->subscribe(Ghost);
        return Ghost;
    }
    case ghostTypes::ORANGE: {
        std::shared_ptr<orangeGhostView> Ghost = std::make_shared<orangeGhostView>(window, _camera, Model->getX(),Model->getY());
        Model->subscribe(Ghost);
        return Ghost;
    }
    default: break;
    }
    return nullptr;
}

std::shared_ptr<packmanView> ConcreteViewFactory::createPacmanView(std::shared_ptr<logic::movableEntity> pacmanModel) {
    std::shared_ptr<packmanView> PacmanView = std::make_shared<packmanView>(window, _camera, pacmanModel->getX(),pacmanModel->getY());
    pacmanModel->subscribe(PacmanView);
    return std::move(PacmanView);
}

std::shared_ptr<wallView> ConcreteViewFactory::createWallView(std::shared_ptr<logic::wall> _wall) {
    return std::make_shared<wallView>(window,_camera,_wall->getX(),_wall->getY());
}

std::shared_ptr<collectableView> ConcreteViewFactory::createCollectableView(std::shared_ptr<logic::collectable> _collectable) {
    if (_collectable->isFruit()) {
        std::shared_ptr<fruitView> fruit = std::make_shared<fruitView>(window,_camera,_collectable->getX(),_collectable->getY());
        _collectable->subscribe(fruit);
        return fruit;
    }
    std::shared_ptr<coinView> coin = std::make_shared<coinView>(window,_camera,_collectable->getX(),_collectable->getY());
    _collectable->subscribe(coin);
    return coin;

}

} // view


