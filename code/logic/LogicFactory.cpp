//
// Created by niels-hertoghs on 12/12/25.
//

#include "LogicFactory.h"


namespace logic {
    std::shared_ptr<Pacman> ConcreteLogicFactory::createPacman(const double x, const double y, float speed) {
        // pacman aanmaken, origin = midpunt
        return std::make_shared<Pacman>(x + 1.f / 20.f, y - 1.f / 14.f, speed);
    }

    std::shared_ptr<collectable> ConcreteLogicFactory::createCollectable(const collectableTypes typeCollectable,
                                                                         const double x,
                                                                         const double y, int points) {
        switch (typeCollectable) {
            case collectableTypes::COIN:
                return std::make_shared<coin>(x + 1.f / 20.f, y - 1.f / 14.f, points);
            case collectableTypes::FRUIT:
                return std::make_shared<fruit>(x + 1.f / 20.f, y - 1.f / 14.f, points);
            default:
                break;
        }
        return nullptr;
    }

    std::shared_ptr<wall> ConcreteLogicFactory::createWall(const double x, const double y) {
        return std::make_shared<wall>(x, y);
    }

    std::shared_ptr<invisibleWall> ConcreteLogicFactory::createInvisibleWall(const double x, const double y) {
        return std::make_shared<invisibleWall>(x, y);
    }

    std::shared_ptr<Ghost> ConcreteLogicFactory::createGhost(ghostTypes typeGhost, double x, double y, float speed,
                                                             int points) {
        switch (typeGhost) {
            case ghostTypes::RED:
                return std::make_shared<redGhost>(x + 1.f / 20.f, y - 1.f / 14.f, speed, points);
            case ghostTypes::GREEN:
                return std::make_shared<greenGhost>(x + 1.f / 20.f, y - 1.f / 14.f, speed, points);
            case ghostTypes::BLUE:
                return std::make_shared<blueGhost>(x + 1.f / 20.f, y - 1.f / 14.f, speed, points);
            case ghostTypes::ORANGE:
                return std::make_shared<orangeGhost>(x + 1.f / 20.f, y - 1.f / 14.f, speed, points);
            default:
                break;
        }
        return nullptr;
    }
} // logic