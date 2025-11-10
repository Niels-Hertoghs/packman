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

    // zien of pack man die richting uit kan gaan
    if (direction != nextDirection && !nextDirection.empty()) {
        // meteen iets verder in het volgende blokje bekijken zodat de buffer geen verschil maakt
        // als je naar de volgende locatie van pacman zou gaan kijken of het een geldige positie was was de kans heel klein dat die naar daar zou gaan, daarom kijkt die ineens naar het blokje verder
        // de buffer is nodig (anders beweegt hij niet), nu kijkt die naar het eerste 1/4 van een blokje om te zien of het een muur is.
        float stepX = 0.f, stepY = 0.f;

        if (nextDirection == "right") stepX = 1/40.f;
        else if (nextDirection == "left") stepX = -1/40.f;
        else if (nextDirection == "up") stepY = 1.f / 28.f;
        else if (nextDirection == "down") stepY = -1.f / 28.f;

        newX = x + stepX;
        newY = y + stepY;

        bool canMove = std::none_of(walls.begin(), walls.end(),
            [&](const std::shared_ptr<wall>& w) { return wouldCollide(w, newX, newY); });

        if (canMove) direction = nextDirection;
    }
    // ga de richting uit
    float dx = 0.f, dy = 0.f;
    if (direction == "right") dx = 0.2f;
    else if (direction == "left") dx = -0.2f;
    else if (direction == "up") dy = 2.f / 7.f;
    else if (direction == "down") dy = -2.f / 7.f;

    // Positie updaten
    x += delta * dx * speed;
    y += delta * dy * speed;



    // zie of de huidige pos niet op een muur staat
    for (auto& w : walls) {
        if (standsOn(w)) {
            prevLocation();
            break;
        }
    }
}

void Packman::updateDir(const std::string& Direction) {
    nextDirection = Direction;
}

void Packman::prevLocation() {
    x = prevX;
    y = prevY;
}


