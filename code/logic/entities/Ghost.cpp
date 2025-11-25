//
// Created by niels_hertoghs on 11/17/25.
//

#include "Ghost.h"

#include <iostream>
#include <utility>

namespace logic {

    /// ---------------------------------------------------------------------------------------------------------------
    /// @class ghost
    /// ---------------------------------------------------------------------------------------------------------------

    Ghost::Ghost(double x, double y) : movableEntity(x,y,0.95f,directions::UP), canChoseDir(false) {}

    std::vector<directions> Ghost::possibleDirections(std::vector<std::shared_ptr<entity>>& walls) {
        std::vector<directions> possibleDirections;

        for (directions dir : {DOWN, UP, RIGHT, LEFT}) {

            double stepX = 0.f, stepY = 0.f;

            // zelfde logica als bij pacman, om te zien of het die richting uit kan gaan.
            if (dir == directions::RIGHT) stepX = 1/80.f;
            else if (dir == directions::LEFT) stepX = -1/80.f;
            else if (dir == directions::UP) stepY = 1.f / 56.f;
            else if (dir == directions::DOWN) stepY = -1.f / 56.f;

            double newX = x + stepX;
            double newY = y + stepY;

            bool canMove = true;

            for (const std::shared_ptr<entity>& w : walls) {
                if (wouldCollide(w,newX,newY)) {
                    canMove = false;
                    break;
                }
            }

            if (canMove) {
                possibleDirections.push_back(dir);
            }
        }
        return possibleDirections;
    }

    void Ghost::changeDirection(directions _direction) {
        prevDirection = direction;
        this->direction = _direction;
    }

    bool Ghost::hadFirstCollision() const {
        return canChoseDir;
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// redGhost
    /// ---------------------------------------------------------------------------------------------------------------

    redGhost::redGhost(double x, double y) : Ghost(x,y) {}

    void redGhost::redGhostSubscribe(std::shared_ptr<view::redGhostView> redGhostObserver) {
        this->ghostObserver = std::move(redGhostObserver);
    }

    void redGhost::update(double deltaTime, std::vector<std::shared_ptr<entity>>& walls) {
        // red ghost de richting laten uitgaan
        this->move(deltaTime);

        // zie of de huidige pos niet op een muur staat
        for (std::shared_ptr<entity>& w : walls) {
            if (standsOn(w) ) {
                prevLocation();

                // hardcode voor de eerste botsing tegen een muur (vanboven uit hun hok)
                if (!canChoseDir) {
                    changeDirection(LEFT);
                    ghostObserver->notify(notifications::CHANGE_DIRECTION_LEFT);
                    canChoseDir = true;
                    hasChosenAtIntersection = true;
                    return;
                }
                this->nextDirection(walls);
                break;
            }
        }

        std::vector<directions> posDirections = this->possibleDirections(walls);

        // Als we NIET op een kruispunt staan → reset gekozen-flag
        // zodat de ghost maar 1 keer kan kiezen per kruispunt (door mijn gebruikte logica, kan die soms meerdere keren kiezen per kruispunt, nu niet meer)
        if (posDirections.size() <= 2) {
            hasChosenAtIntersection = false;
        }

        // kruispunten detecteren, en eventueel de richting uitgaan (niet terug draaien)
        if (posDirections.size() > 2 && canChoseDir && !hasChosenAtIntersection) {
            hasChosenAtIntersection = true; // zodat die niet meerdere keren kiest aan dit kruispunt

            // verwijder de omgekeerde richting, zodat het niet kan terug keren op een kruispunt
            directions forbidden = oppositeDirection(direction);
            if (forbidden == EMPTY) {
                return;
            }

            std::vector<directions> filteredDirections;

            for (directions d : posDirections) {
                if (d != forbidden) {
                    filteredDirections.push_back(d);
                }
            }

            // verander van richting
            if (!filteredDirections.empty()) {
                int chosenDir = random::getInstance()->getNumber(0, filteredDirections.size());;

                changeDirection(filteredDirections[chosenDir]);

                // notify
                if (direction == directions::RIGHT)      ghostObserver->notify(notifications::CHANGE_DIRECTION_RIGHT);
                else if (direction == directions::LEFT)  ghostObserver->notify(notifications::CHANGE_DIRECTION_LEFT);
                else if (direction == directions::UP)    ghostObserver->notify(notifications::CHANGE_DIRECTION_UP);
                else if (direction == directions::DOWN)  ghostObserver->notify(notifications::CHANGE_DIRECTION_DOWN);
            }

        }

        ghostObserver->notify(notifications::CHANGE_POSITION);
    }

    void redGhost::nextDirection(std::vector<std::shared_ptr<entity>>& walls) {

        std::vector<directions> possibleDirections = this->possibleDirections(walls);


        if (possibleDirections.empty()) {
            return;
        }

        int chosenDir = random::getInstance()->getNumber(0, possibleDirections.size());

        changeDirection(possibleDirections[chosenDir]);

        // observer notfyen
        if (direction == directions::RIGHT) {
            ghostObserver->notify(notifications::CHANGE_DIRECTION_RIGHT);
        } else if (direction == directions::LEFT) {
            ghostObserver->notify(notifications::CHANGE_DIRECTION_LEFT);
        } else if (direction == directions::UP) {
            ghostObserver->notify(notifications::CHANGE_DIRECTION_UP);
        } else if (direction == directions::DOWN) {
            ghostObserver->notify(notifications::CHANGE_DIRECTION_DOWN);
        }
    }

    void redGhost::died() {
        toSpawnLocation();
        canChoseDir = false;
        if (direction == directions::RIGHT) {
            ghostObserver->notify(notifications::CHANGE_DIRECTION_RIGHT);
        } else if (direction == directions::LEFT) {
            ghostObserver->notify(notifications::CHANGE_DIRECTION_LEFT);
        } else if (direction == directions::UP) {
            ghostObserver->notify(notifications::CHANGE_DIRECTION_UP);
        } else if (direction == directions::DOWN) {
            ghostObserver->notify(notifications::CHANGE_DIRECTION_DOWN);
        }
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// blueGhost
    /// ---------------------------------------------------------------------------------------------------------------


    blueGhost::blueGhost(double x, double y)  : Ghost(x,y) {}

    void blueGhost::givePacman(std::shared_ptr<logic::Packman> _pacman) {
        pacman = std::move(_pacman);
    }


    void blueGhost::blueGhostSubscribe(std::shared_ptr<view::blueGhostView>& _ghostObserver) {
        ghostObserver = _ghostObserver;
    }

    void blueGhost::update(double deltaTime, std::vector<std::shared_ptr<entity>>& walls) {
        this->move(deltaTime);

        for (std::shared_ptr<entity>& w : walls) {
            if (standsOn(w) ) {
                prevLocation();

                // hardcode voor de eerste botsing tegen een muur (vanboven uit hun hok)
                if (!canChoseDir) {
                    changeDirection(LEFT);
                    ghostObserver->notify(notifications::CHANGE_DIRECTION_LEFT);
                    canChoseDir = true;
                    return;
                }
            }
        }

        std::vector<directions> posDirections = this->possibleDirections(walls);

        // "de voorkant" van pacman, op dat moment
        std::pair<double, double> voorkantPac = pacman->getFront(pacman->get_direction());

        // initializatie om de richting te kiezen
        directions nextDirection = direction;
        double minDistance = std::numeric_limits<double>::max();

        if (canChoseDir) {
            for (directions d : posDirections) {
                // std::pair<double, double> voorkantGhost = this->getFront(direction);
                // de pos van het spookje als het direction p op gaat
                std::pair<double,double> nextPosGhost = calculateNextPos(deltaTime,d,x + 1.f/20.f,y - 1.f/14.f);
                double distance = calculateManhatten(voorkantPac.first,voorkantPac.second,nextPosGhost.first,nextPosGhost.second);
                if (distance < minDistance) {
                    minDistance = distance;
                    nextDirection = d;
                }
            }
        }

        changeDirection(nextDirection);
        // this->move(deltaTime);


        // notify
        if (direction == directions::RIGHT)      ghostObserver->notify(notifications::CHANGE_DIRECTION_RIGHT);
        else if (direction == directions::LEFT)  ghostObserver->notify(notifications::CHANGE_DIRECTION_LEFT);
        else if (direction == directions::UP)    ghostObserver->notify(notifications::CHANGE_DIRECTION_UP);
        else if (direction == directions::DOWN)  ghostObserver->notify(notifications::CHANGE_DIRECTION_DOWN);
        ghostObserver->notify(notifications::CHANGE_POSITION);
    }

    double blueGhost::calculateManhatten(double x1, double y1, double x2, double y2) {
        double x = std::abs(x1 - x2);
        double y = std::abs(y1 - y2);
        return x + y;
    }



    void blueGhost::died() {

    }


    void blueGhost::nextDirection(std::vector<std::shared_ptr<entity>>& walls) {
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// purpleGhost
    /// ---------------------------------------------------------------------------------------------------------------


    purpleGhost::purpleGhost(double x, double y)  : Ghost(x,y) {}

    void purpleGhost::purpleGhostSubscribe(std::shared_ptr<view::purpleGhostView> _ghostObserver) {
        ghostObserver = _ghostObserver;
    }


    void purpleGhost::update(double deltaTime, std::vector<std::shared_ptr<entity>>& walls) {

    }


    void purpleGhost::died() {

    }


    void purpleGhost::nextDirection(std::vector<std::shared_ptr<entity>>& walls) {
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// greenGhost
    /// ---------------------------------------------------------------------------------------------------------------


    greenGhost::greenGhost(double x, double y)  : Ghost(x,y) {}

    void greenGhost::greenGhostSubscribe(std::shared_ptr<view::greenGhostView> _ghostObserver) {
        ghostObserver = _ghostObserver;
    }

    void greenGhost::update(double deltaTime, std::vector<std::shared_ptr<entity>>& walls) {

    }


    void greenGhost::died() {

    }


    void greenGhost::nextDirection(std::vector<std::shared_ptr<entity>>& walls) {
    }


} // logic