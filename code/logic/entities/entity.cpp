//
// Created by niels on 11/5/25.
//

#include "entity.h"

namespace logic {
    /// ---------------------------------------------------------------------------------------------------------------
    /// @class entity
    /// ---------------------------------------------------------------------------------------------------------------

    entity::entity(const double x, const double y) : x(x), y(y) {}

    double entity::getX() const {
        return x;
    }

    double entity::getY() const {
        return y;
    }

    std::pair<double,double> entity::getPosition() const {
        return {x,y};
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// @class wall
    /// ---------------------------------------------------------------------------------------------------------------

    wall::wall(double x, double y) : entity(x, y) {}

    invisibleWall::invisibleWall(const double x, const double y) : entity(x, y) {    }

}