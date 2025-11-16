//
// Created by niels on 11/6/25.
//

#include "movableEntity.h"

#include "../../render/render.h"

namespace logic {
    /// ---------------------------------------------------------------------------------------------------------------
    /// @class movableEntity
    /// ---------------------------------------------------------------------------------------------------------------

    movableEntity::movableEntity(double x, double y, double speed) : entity(x, y), direction(directions::RIGHT), speed(speed) {}

    bool movableEntity::standsOn(const std::shared_ptr<entity>& other) {
        return this->wouldCollide(other,x,y);
    }

    bool movableEntity::wouldCollide(const std::shared_ptr<entity>& other, double nextX, double nextY) {
        double width = 1.f / 10.f;
        double height = 1.f / 7.f;

        double pacX = nextX - 1.f/20.f;
        double pacY = nextY + 1.f/14.f;

        double buffer = 0.005f;

        bool overlapX = pacX < other->getX() + width - buffer && pacX + width > other->getX() + buffer;
        bool overlapY = pacY > other->getY() - height + buffer && pacY - height < other->getY() - buffer;
        return overlapX && overlapY;
    }

    void movableEntity::prevLocation() {
        x = prevX;
        y = prevY;
    }


    /// ---------------------------------------------------------------------------------------------------------------
    /// @class Packman
    /// ---------------------------------------------------------------------------------------------------------------

    Packman::Packman(double x, double y)  : movableEntity(x,y,1.f), nextDirection(EMPTY) {}

    void Packman::render(std::shared_ptr<render::Render> render) {
        render->addPackman(this->getX(),this->getY());
    }

    void Packman::update(double delta,std::vector<std::shared_ptr<wall>>& walls) {

        prevX = this->getX();
        prevY = this->getY();

        double newX = x;
        double newY = y;

        // zien of pack man die richting uit kan gaan
        if (direction != nextDirection && nextDirection != EMPTY) {
            // meteen iets verder in het volgende blokje bekijken zodat de buffer geen verschil maakt
            // als je naar de volgende locatie van pacman zou gaan kijken of het een geldige positie was was de kans heel klein dat die naar daar zou gaan, daarom kijkt die ineens naar het blokje verder
            // de buffer is nodig (anders beweegt hij niet), nu kijkt die naar het eerste 1/8 van een blokje om te zien of het een muur is.
            // 1/8, is redelijk kklein maar ook niet te klein dat het foutgen geeft, in mijn testen
            double stepX = 0.f, stepY = 0.f;

            if (nextDirection == directions::RIGHT) stepX = 1/80.f;
            else if (nextDirection == directions::LEFT) stepX = -1/80.f;
            else if (nextDirection == directions::UP) stepY = 1.f / 56.f;
            else if (nextDirection == directions::DOWN) stepY = -1.f / 56.f;

            newX = x + stepX;
            newY = y + stepY;

            bool canMove = std::none_of(walls.begin(), walls.end(),
                [&](const std::shared_ptr<wall>& w) { return wouldCollide(w, newX, newY); });

            if (canMove) direction = nextDirection;
        }
        // ga de richting uit
        double dx = 0.f, dy = 0.f;
        if (direction == directions::RIGHT) dx = 0.2f;
        else if (direction == directions::LEFT) dx = -0.2f;
        else if (direction == directions::UP) dy = 2.f / 7.f;
        else if (direction == directions::DOWN) dy = -2.f / 7.f;

        // Positie updaten
        x += delta * dx * speed;
        y += delta * dy * speed;



        // zie of de huidige pos niet op een muur staat
        for (std::shared_ptr<wall>& w : walls) {
            if (standsOn(w)) {
                prevLocation();
                break;
            }
        }
    }

    void Packman::updateDir(enum directions dir) {
        nextDirection = dir;
    }

    bool Packman::standsOnCoin(const std::shared_ptr<entity>& other) {
        double radiusx = 0.016f + 1/30.f; // kan aangepast worden, de 30 groter maken betekent dat de coin dichter bij het centrum van pacman moet zijn
        double radiusy = 0.016f + 1/15.f;


        double pacX = x;
        double pacY = y;

        double buffer = 0.001f;

        bool overlapX = pacX < other->getX() + radiusx - buffer && pacX + radiusx > other->getX() + buffer;
        bool overlapY = pacY > other->getY() - radiusy + buffer && pacY - radiusy < other->getY() - buffer;
        return overlapX && overlapY;
    }

    void Packman::pacmanSubscribe(std::shared_ptr<view::packmanView> PacmanObserver) {
        packmanObserver = PacmanObserver;
    }


    /// ---------------------------------------------------------------------------------------------------------------
    /// @class ghost
    /// ---------------------------------------------------------------------------------------------------------------
}