//
// Created by niels on 11/6/25.
//

#include "movableEntity.h"

#include "../render.h"

movableEntity::movableEntity(float x, float y, float speed) : entity(x, y), direction("right"), speed(speed) {}

Packman::Packman(float x, float y)  : movableEntity(x,y,1.f) {}

void Packman::render(std::shared_ptr<Render> render) {
    render->addPackman(this->getX(),this->getY());
}

void Packman::update(float delta) {
    if (direction == "right") {
        x = x + (delta*0.2 * speed);
    } else if (direction == "left") {
        x = x - (delta*0.2) * speed;
    } else if (direction == "up") {
        y = y + (delta* (2.f/7.f) * speed);
    } else if (direction == "down") {
        y = y - (delta* (2.f/7.f) * speed);
    }
}

void Packman::updateDir(const std::string& Direction) {
    direction = Direction;
}

