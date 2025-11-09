//
// Created by niels on 11/6/25.
//

#include "collectable.h"

#include "../render.h"

collectable::collectable(float x, float y) : entity(x,y ){}

coin::coin(float x, float y) : collectable(x,y){}

void coin::render(std::shared_ptr<Render> render) {
    render->addCoin(this->getX(),this->getY());
}

fruit::fruit(float x, float y) : collectable(x,y){}


void fruit::render(std::shared_ptr<Render> render) {
    render->addFruit(this->getX(),this->getY());
}

