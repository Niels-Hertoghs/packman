//
// Created by niels on 11/6/25.
//

#include "movableEntity.h"
#include "Ghost.h"
#include <utility>


namespace logic {
    /// ---------------------------------------------------------------------------------------------------------------
    /// @class movableEntity
    /// ---------------------------------------------------------------------------------------------------------------

    movableEntity::movableEntity(double x, double y, double speed,directions dir)
    : entity(x, y), direction(dir),originalDirection(dir), speed(speed),spawnLocatieX(x),spawnLocatieY(y),prevX(x),prevY(y) {}

    bool movableEntity::standsOn(const std::shared_ptr<entity>& other) {
        return wouldCollide(other,x,y);
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

    directions movableEntity::oppositeDirection(directions dir) {
        switch(dir) {
        case UP: return DOWN;
        case DOWN: return UP;
        case LEFT: return RIGHT;
        case RIGHT: return LEFT;
        default: return EMPTY;
        }
    }


    void movableEntity::move(double delta) {
        // ga de richting uit
        prevX = this->getX();
        prevY = this->getY();

        std::pair<double,double> nextPos = calculateNextPos(delta,direction,x,y);

        x = nextPos.first;
        y = nextPos.second;
    }

    std::pair<double,double> movableEntity::calculateNextPos(double delta, directions dir,double _x,double _y) const {
        double dx = 0.f, dy = 0.f;
        if (dir == directions::RIGHT) dx = 0.2f;
        else if (dir == directions::LEFT) dx = -0.2f;
        else if (dir == directions::UP) dy = 2.f / 7.f;
        else if (dir == directions::DOWN) dy = -2.f / 7.f;

        // Positie updaten
        double nextX = (delta * dx * speed) + _x;
        double nextY = (delta * dy * speed) + _y;

        return {nextX,nextY};

    }

    void movableEntity::toSpawnLocation() {
        x = spawnLocatieX;
        y = spawnLocatieY;
        direction = originalDirection;
        notifyDir();
        notifyPos();

    }

    std::pair<double, double> movableEntity::getFront() {
        return getCoSide(direction);
    }

    std::pair<double,double> movableEntity::getBack() {
        return getCoSide(oppositeDirection(direction));
    }

    std::pair<double,double> movableEntity::getCoSide(directions dir) {
        std::pair<double, double> pos = {x,y};
        if (dir == directions::RIGHT || dir == directions::LEFT) {
            pos.second = y - 1.f / 14.f;
            if (dir == directions::RIGHT) {
                pos.first = x + 1.f/10.f;
            }
        } else if (dir == directions::UP || dir == directions::DOWN) {
            pos.first = x + 1.f / 20.f;
            if (dir == directions::DOWN) {
                pos.second = y - 1.f / 7.f;
            }
        }

        return pos;
    }

    void movableEntity::notifyPos() const {
        observer->notify(notifications::CHANGE_POSITION);
    }

    void movableEntity::notifyDir() const {
        if (direction == directions::RIGHT) {
            observer->notify(notifications::CHANGE_DIRECTION_RIGHT);
        } else if (direction == directions::LEFT) {
            observer->notify(notifications::CHANGE_DIRECTION_LEFT);
        } else if (direction == directions::UP) {
            observer->notify(notifications::CHANGE_DIRECTION_UP);
        } else {
            observer->notify(notifications::CHANGE_DIRECTION_DOWN);
        }
    }


    directions movableEntity::get_direction() const {
        return direction;
    }

    void movableEntity::subscribe(const std::shared_ptr<view::movableEntityView>& Observer) {
        observer = Observer;
    }


    /// ---------------------------------------------------------------------------------------------------------------
    /// @class Pacman
    /// ---------------------------------------------------------------------------------------------------------------

    Pacman::Pacman(double x, double y,double speed)  : movableEntity(x,y,speed,directions::RIGHT), nextDirection(EMPTY) {}

    void Pacman::update(double delta,std::vector<std::shared_ptr<entity>>& walls) {
        //TODO: zien wat van walls er const mag zijn (mss getters ook const makern)

        double newX = x;
        double newY = y;

        // zien of pack man die richting uit kan gaan
        if (direction != nextDirection && nextDirection != EMPTY) {
            // meteen iets verder in het volgende blokje bekijken zodat de buffer geen verschil maakt
            // als je naar de volgende locatie van pacman zou gaan kijken of het een geldige positie was was de kans heel klein dat die naar daar zou gaan, daarom kijkt die ineens naar het blokje verder
            // de buffer is nodig (anders beweegt hij niet), nu kijkt die naar het eerste 1/8 van een blokje om te zien of het een muur is.
            // 1/8, is redelijk kklein maar ook niet te klein dat het foutgen geeft, in mijn testen

            // de positie berekenen
            double stepX = 0.f, stepY = 0.f;


            if (nextDirection == directions::RIGHT) stepX = 1/80.f;
            else if (nextDirection == directions::LEFT) stepX = -1/80.f;
            else if (nextDirection == directions::UP) stepY = 1.f / 56.f;
            else if (nextDirection == directions::DOWN) stepY = -1.f / 56.f;

            newX += stepX;
            newY += stepY;


            // kijken of er daar geen wall staat
            bool canMove = true;

            for (const std::shared_ptr<entity>& w : walls) {
                if (wouldCollide(w,newX,newY)) {
                    canMove = false;
                    break;
                }
            }

            if (canMove) {
                direction = nextDirection;
                notifyDir();
            }
        }

        // De movable laten bewegen in de direction.
        this->move(delta);

        // zie of de huidige pos niet op een muur staat
        for (std::shared_ptr<entity>& w : walls) {
            if (standsOn(w)) {
                prevLocation();
                break;
            }
        }
        notifyPos();
    }

    void Pacman::updateDir(enum directions dir) {
        nextDirection = dir;
    }

    bool Pacman::standsOnCoin(const std::shared_ptr<entity>& other) {
        // de radius van de coin, moet hetzelfde zijn als in de collectableView
        double radiusx = 0.016f + 1/30.f; // kan aangepast worden, de 30 groter maken betekent dat de coin dichter bij het centrum van pacman moet zijn
        double radiusy = 0.016f + 1/15.f;


        double pacX = x;
        double pacY = y;

        double buffer = 0.001f;

        bool overlapX = pacX < other->getX() + radiusx - buffer && pacX + radiusx > other->getX() + buffer;
        bool overlapY = pacY > other->getY() - radiusy + buffer && pacY - radiusy < other->getY() - buffer;
        return overlapX && overlapY;
    }

    bool Pacman::standsOnGhost(const std::shared_ptr<Ghost>& ghost) {
        double width = 1.f / 10.f;
        double height = 1.f / 7.f;

        double pacX = x - 1.f/20.f;
        double pacY = y + 1.f/14.f;

        double ghostX = ghost->getX() - 1.f/20.f;
        double ghostY = ghost->getY() + 1.f/14.f;

        // hoe hoger ghoe dichter bij het centrum van pacman de ghost moet zijn voor het er op staat.
        double buffer = 0.035f;

        bool overlapX = pacX < ghostX + width - buffer && pacX + width > ghostX + buffer;
        bool overlapY = pacY > ghostY - height + buffer && pacY - height < ghostY - buffer;
        return overlapX && overlapY;
    }


    void Pacman::died() {
        toSpawnLocation();
        nextDirection = EMPTY; // is iets prive van pacman.
        notifyDir();
        notifyPos();
    }


}