//
// Created by niels on 11/5/25.
//

#include "entity.h"
#include "../render.h"

/// ---------------------------------------------------------------------------------------------------------------
/// @class entity
/// ---------------------------------------------------------------------------------------------------------------

entity::entity(float x,float y) : x(x), y(y) {}

float entity::getX() const {
    return x;
}

float entity::getY() const {
    return y;
}

/// ---------------------------------------------------------------------------------------------------------------
/// @class wall
/// ---------------------------------------------------------------------------------------------------------------

wall::wall(float x, float y) : entity(x, y) {}

void wall::render(std::shared_ptr<Render> render) {
    render->addWall(this->getX(),this->getY());
}
