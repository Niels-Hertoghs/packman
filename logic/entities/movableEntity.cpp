//
// Created by niels on 11/6/25.
//

#include "movableEntity.h"

#include "../render.h"

movableEntity::movableEntity(float x, float y, float speed) : entity(x, y), direction("right"), speed(speed) {}

bool movableEntity::standsOn(const std::shared_ptr<entity>& other) {
    float buffer = 0.01f;
    float width = 1.f / 10.f;
    float height = 1.f / 7.f;

    float pacX = x - 1.f/20.f;
    float pacY = y + 1.f/14.f;

    float pacX2 = pacX + 1.f/10.f;
    float pacY2 = pacY - 1.f/14.f;

    // float pacX3 = pacX2;
    // float pacY3 = pacY;
    //
    // float pacX4 = pacX;
    // float pacY4 = pacY2;

    float leftB = other->getX() + buffer;
    float rightB = leftB + width - buffer;
    float topB = other->getY() - buffer;
    float bottomB = topB - height + buffer;

    if ((leftB < pacX  && pacX  < rightB && topB > pacY  && pacY  > bottomB) ||
        (leftB < pacX2 && pacX2 < rightB && topB > pacY2 && pacY2 > bottomB) ) {
        return true;
        }
    return false;
}


Packman::Packman(float x, float y)  : movableEntity(x,y,1.f) {}

void Packman::render(std::shared_ptr<Render> render) {
    render->addPackman(this->getX(),this->getY());
}

void Packman::update(float delta) {
    prevX = this->getX();
    prevY = this->getY();
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
    prevDirection = direction;
    direction = Direction;
}

void Packman::prevLocation() {
    // direction = prevDirection;
    x = prevX;
    y = prevY;
}


