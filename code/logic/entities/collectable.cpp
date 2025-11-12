//
// Created by niels on 11/6/25.
//

#include "collectable.h"

#include "../../render/render.h"
namespace logic {
    /// ---------------------------------------------------------------------------------------------------------------
    /// @class collectable
    /// ---------------------------------------------------------------------------------------------------------------
    ///
    collectable::collectable(double x, double y,double Points) : entity(x,y ), points(Points) {}

    double collectable::getPoints() {
        return points;
    }

    void collectable::setPoints(double newPoints) {
        points = newPoints;
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// @class coin
    /// ---------------------------------------------------------------------------------------------------------------

    coin::coin(double x, double y,double points) : collectable(x,y,points){}

    void coin::render(std::shared_ptr<render::Render> render) {
        render->addCoin(this->getX(),this->getY());
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// @class fruit
    /// ---------------------------------------------------------------------------------------------------------------

    fruit::fruit(double x, double y,double points) : collectable(x,y,points){}


    void fruit::render(std::shared_ptr<render::Render> render) {
        render->addFruit(this->getX(),this->getY());
    }
}
