//
// Created by niels on 11/5/25.
//

#include "entity.h"

namespace logic {
/// ---------------------------------------------------------------------------------------------------------------
/// @class entity
/// ---------------------------------------------------------------------------------------------------------------

entity::entity(const double x, const double y)
    : x(x), y(y) {
}

double entity::getX() const {
    return x;
}

double entity::getY() const {
    return y;
}

std::pair<double, double> entity::getPosition() const {
    return {x, y};
}

void entity::subscribe(std::shared_ptr<Observer<notifications>> Observer) {
    observers.push_back(std::move(Observer));
}

void entity::notifyObservers(const notifications& notification) {
    for (const auto& observer : observers) {
        observer->notify(notification);
    }
}


/// ---------------------------------------------------------------------------------------------------------------
/// @class wall
/// ---------------------------------------------------------------------------------------------------------------

wall::wall(const double x, const double y)
    : entity(x, y) {
}

/// ---------------------------------------------------------------------------------------------------------------
/// @class invisibleWall
/// ---------------------------------------------------------------------------------------------------------------

invisibleWall::invisibleWall(const double x, const double y)
    : entity(x, y) {
}
}
