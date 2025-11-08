//
// Created by niels on 11/6/25.
//

#include "movableEntity.h"

#include "../render.h"

movableEntity::movableEntity(float x, float y) : entity(x, y), direction("right") {}

Packman::Packman(float x, float y)  : movableEntity(x,y) {}

void Packman::render(Render *render) {
    render->addPackman(this->getX(),this->getY());
}

void Packman::update(float delta) {
    if (direction == "right") {
        x = x + (delta*0.1);
    } else if (direction == "left") {
        x = x - delta*0.1;
    } else if (direction == "up") {
        y = y + (delta*0.1);
    } else if (direction == "down") {
        y = y - delta*0.1;
    }
}

void Packman::updateDir(const std::string& Direction) {
    direction = Direction;
}

