//
// Created by niels on 11/6/25.
//

#include "collectable.h"

#include "../render.h"

/// ---------------------------------------------------------------------------------------------------------------
/// @class collectable
/// ---------------------------------------------------------------------------------------------------------------
///
collectable::collectable(float x, float y,float Points) : entity(x,y ), points(Points) {}

float collectable::getPoints() {
    return points;
}

void collectable::setPoints(float newPoints) {
    points = newPoints;
}

/// ---------------------------------------------------------------------------------------------------------------
/// @class coin
/// ---------------------------------------------------------------------------------------------------------------

coin::coin(float x, float y,float points) : collectable(x,y,points){}

void coin::render(std::shared_ptr<Render> render) {
    render->addCoin(this->getX(),this->getY());
}

/// ---------------------------------------------------------------------------------------------------------------
/// @class fruit
/// ---------------------------------------------------------------------------------------------------------------

fruit::fruit(float x, float y,float points) : collectable(x,y,points){}


void fruit::render(std::shared_ptr<Render> render) {
    render->addFruit(this->getX(),this->getY());
}

