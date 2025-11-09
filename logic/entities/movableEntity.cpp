//
// Created by niels on 11/6/25.
//

#include "movableEntity.h"

#include "../render.h"

movableEntity::movableEntity(float x, float y, float speed) : entity(x, y), direction("right"), speed(speed) {}

bool movableEntity::standsOn(const std::shared_ptr<entity>& other) {
    return this->wouldCollide(other,x,y);
}

bool movableEntity::wouldCollide(const std::shared_ptr<entity>& other, float nextX, float nextY) {
    float width = 1.f / 10.f;
    float height = 1.f / 7.f;

    float pacX = nextX - 1.f/20.f;
    float pacY = nextY + 1.f/14.f;

    float buffer = 0.001f;

    bool overlapX = pacX < other->getX() + width - buffer && pacX + width > other->getX() + buffer;
    bool overlapY = pacY > other->getY() - height + buffer && pacY - height < other->getY() - buffer;
    return overlapX && overlapY;
}

Packman::Packman(float x, float y)  : movableEntity(x,y,1.f), nextDirection("") {}

void Packman::render(std::shared_ptr<Render> render) {
    render->addPackman(this->getX(),this->getY());
}

void Packman::update(float delta,std::vector<std::shared_ptr<wall>>& walls) {


    prevX = this->getX();
    prevY = this->getY();

    float newX = x;
    float newY = y;

    if (direction != nextDirection && !nextDirection.empty()) {
        if (nextDirection == "right") {
            newX = x + 1/10.f;
        } else if (nextDirection == "left") {
            newX = x - 1/10.f;
        } else if (nextDirection == "up") {
            newY = y + 1/7.f;
        } else if (nextDirection == "down") {
            newY = y - 1/7.f;
        }
        bool canMove = true;
        for (std::shared_ptr<wall>& wall : walls) {
            if (wouldCollide(wall,newX,newY)) {
                canMove = false;
                // this->prevLocation();

                break;
            }
        }
        if (canMove) {
            direction = nextDirection;
            // return;
        }
    }
    if (direction == "right") {
        x = x + (delta*0.2 * speed);
    } else if (direction == "left") {
        x = x - (delta*0.2) * speed;
    } else if (direction == "up") {
        y = y + (delta* (2.f/7.f) * speed);
    } else if (direction == "down") {
        y = y - (delta* (2.f/7.f) * speed);
    }

     for (std::shared_ptr<wall>& wall : walls) {
         if (this->standsOn(wall)) {
             this->prevLocation();
         }
     }
}

void Packman::updateDir(const std::string& Direction) {

    nextDirection = Direction;

    // prevDirection = direction;
    // direction = Direction;
}

void Packman::prevLocation() {
    // direction = prevDirection;
    x = prevX;
    y = prevY;
}


