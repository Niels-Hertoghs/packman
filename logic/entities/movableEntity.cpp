//
// Created by niels on 11/6/25.
//

#include "movableEntity.h"

#include "../render.h"

movableEntity::movableEntity(float x, float y) : entity(x, y) {}

Packman::Packman(float x, float y)  : movableEntity(x,y) {}

void Packman::render(Render *render) {
    render->addPackman(this->getX(),this->getY());
}

void Packman::update(float delta) {
    x = x + (delta*0.1);
}
