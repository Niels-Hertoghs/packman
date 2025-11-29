//
// Created by niels_hertoghs on 11/17/25.
//

#include "Ghost.h"

namespace logic {

    /// ---------------------------------------------------------------------------------------------------------------
    /// @class Ghost
    /// ---------------------------------------------------------------------------------------------------------------

    Ghost::Ghost(const double x, const double y, const bool outsideCage, const directions direction, const double speed, const int _points)
        : movableEntity(x, y, speed, direction), canChoseDir(false), hasChosenAtIntersection(false),
          prevDirection(directions::EMPTY), mode(modes::CHASING_MODE), outsideCage(outsideCage),
          originalOutsideCage(outsideCage),points(_points) {
    }

    void Ghost::update(double deltaTime, std::vector<std::shared_ptr<entity> > &walls) {
        // ghost de richting laten uitgaan
        // als het als mag vertrekken (green na 5 sec, orange na 10 sec)
        if (canMove()) {
            this->move(deltaTime);

            // als die nog in de cage zit, eerst omhoog laten gaan, als het gaat, om er zo uit te gaan
            if (!outsideCage) {
                std::vector<directions> possibleDirections = this->possibleDirections(walls);
                if (std::find(possibleDirections.begin(), possibleDirections.end(), UP) != possibleDirections.end()) {
                    direction = UP;
                    outsideCage = true;
                    notifyDir();
                }
            }
        } else {
            return;
        }

        // zie of de huidige pos niet op een muur staat
        for (std::shared_ptr<entity>& w : walls) {
            if (standsOn(w) ) {
                prevLocation();

                // voor de eerste botsing tegen een muur (vanboven uit hun hok), dan kunnen ze elke kant op gaan
                // ze kunnen in het begin 1 keer door de invisible wall, daarna niet meer
                if (!canChoseDir) {
                    canChoseDir = true;
                    hasChosenAtIntersection = true;
                    outsideCage = true;
                    nextDirection(walls);
                    return;
                }
                this->nextDirection(walls);
                break;
            }
        }

        const std::vector<directions> posDirections = this->possibleDirections(walls);

        // Als we niet op een kruispunt staan → reset gekozen-flag
        // zodat de ghost maar 1 keer kan kiezen per kruispunt (door mijn gebruikte logica, kan die soms meerdere keren kiezen per kruispunt, nu niet meer)
        if (posDirections.size() <= 2) {
            hasChosenAtIntersection = false;
        }

        // kruispunten detecteren
        if (posDirections.size() > 2 && canChoseDir && !hasChosenAtIntersection) {
            hasChosenAtIntersection = true; // zodat die niet meerdere keren kiest aan dit kruispunt
            this->chooseAtIntersection(walls);
        }
        notifyPos();
    }


    std::vector<directions> Ghost::possibleDirections(const std::vector<std::shared_ptr<entity>>& walls) const {
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

    bool Ghost::hadFirstCollision() const {
        return canChoseDir && outsideCage;
    }

    void Ghost::changeDirection(directions _direction) {
        prevDirection = direction;
        this->direction = _direction;
        notifyDir();
    }

    void Ghost::startFearMode() {
        mode = modes::FEAR_MODE;
        observer->notify(notifications::TO_FEAR_MODE);
        // snelheid van de ghost wordt gehalveerd in fearMode
        speed *= 0.5f;
    }

    void Ghost::startChaseMode() {
        // als het al eens opgegeten was, is alles al veranderd
        if (mode == CHASING_MODE) {
            return;
        }
        mode = CHASING_MODE;
        observer->notify(notifications::TO_CHASING_MODE);
        notifyDir();
        // snelheid van de ghost gaat terug naar de originele snelheid (was gehalveerd dus nu keer 2).
        speed *= 2.f;
    }

    int Ghost::getGhostPoints() const {
        return points;
    }


    void Ghost::died() {
        toSpawnLocation();
        canChoseDir = false; // prive van ghost
        outsideCage = originalOutsideCage;\

        if (mode == FEAR_MODE) {
            // moet terug naar chasing mode gaan en de snelheid moet terug naar originele gaan.
            startChaseMode();
        }
    }

    enum modes Ghost::get_mode() const {
        return mode;
    }


    /// ---------------------------------------------------------------------------------------------------------------
    /// redGhost
    /// ---------------------------------------------------------------------------------------------------------------

    redGhost::redGhost(const double x, const double y, const double speed, const int points) : Ghost(x,y, true,UP,speed,points) {}

    void redGhost::redGhostSubscribe(const std::shared_ptr<view::redGhostView>& redGhostObserver) {
        observer = redGhostObserver;
    }

    void redGhost::nextDirection(std::vector<std::shared_ptr<entity>>& walls) {

        const std::vector<directions> possibleDirections = this->possibleDirections(walls);

        if (possibleDirections.empty()) {
            return;
        }
        int chosenDir = random::getInstance()->getNumber(0, static_cast<int>(possibleDirections.size()));
        changeDirection(possibleDirections[chosenDir]);
    }

    void redGhost::chooseAtIntersection(std::vector<std::shared_ptr<entity> > &walls) {

        const std::vector<directions> posDirections = this->possibleDirections(walls);

        // verwijder de omgekeerde richting, zodat het niet kan terug keren op een kruispunt
        directions forbidden = oppositeDirection(direction);
        if (forbidden == EMPTY) {
            return;
        }

        // haalt de kant waar het vandaan komt eruit, zodat het niet terug in die richting kan gaan.
        std::vector<directions> filteredDirections;
        for (directions d : posDirections) {
            if (d != forbidden) {
                filteredDirections.push_back(d);
            }
        }

        // verander van richting
        if (!filteredDirections.empty()) {
            int chosenDir = random::getInstance()->getNumber(0, static_cast<int>(filteredDirections.size()));;

            changeDirection(filteredDirections[chosenDir]);
        }
    }

    bool redGhost::canMove() {
        return true;
    }
} // logic