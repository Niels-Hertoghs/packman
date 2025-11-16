//
// Created by niels on 11/5/25.
//

#include "entity.h"

namespace logic {
    /// ---------------------------------------------------------------------------------------------------------------
    /// @class entity
    /// ---------------------------------------------------------------------------------------------------------------

    entity::entity(double x,double y) : x(x), y(y) {}

    double entity::getX() const {
        return x;
    }

    double entity::getY() const {
        return y;
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// @class wall
    /// ---------------------------------------------------------------------------------------------------------------

    wall::wall(double x, double y) : entity(x, y) {}

    std::pair<double,double> wall::getPosition() const {
        return std::pair<double,double>(this->x,this->y);
    }

    void wall::wallSubscribe(std::shared_ptr<view::wallView> wallObserver) {
        _wallObserver = wallObserver;
    }

}