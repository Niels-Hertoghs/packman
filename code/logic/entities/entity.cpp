//
// Created by niels on 11/5/25.
//

#include "entity.h"
#include "../../render/render.h"

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

    void wall::render(std::shared_ptr<render::Render> render) {
        render->addWall(this->getX(),this->getY());
    }

    std::pair<double,double> wall::getPosition() const {
        return std::pair<double,double>(this->x,this->y);
    }

    void wall::wallSubscribe(std::shared_ptr<wallView>* wallObserver) {
        _wallObserver = wallObserver;
    }

}