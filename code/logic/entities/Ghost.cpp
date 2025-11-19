//
// Created by niels_hertoghs on 11/17/25.
//

#include "Ghost.h"

#include <iostream>

namespace logic {

    /// ---------------------------------------------------------------------------------------------------------------
    /// @class ghost
    /// ---------------------------------------------------------------------------------------------------------------

    Ghost::Ghost(double x, double y) : movableEntity(x,y,0.95f,directions::UP), canChoseDir(false) {}

    std::vector<directions> Ghost::possibleDirections(std::vector<std::shared_ptr<entity>>& walls) {
        std::vector<directions> possibleDirections;

        for (directions dir : {DOWN, UP, RIGHT, LEFT}) {


            double stepX = 0.f, stepY = 0.f;

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

    redGhost::redGhost(double x, double y) : Ghost(x,y) {}

    void redGhost::redGhostSubscribe(std::shared_ptr<view::redGhostView> redGhostObserver) {
        this->ghostObserver = redGhostObserver;
    }

    void redGhost::update(double deltaTime, std::vector<std::shared_ptr<entity>>& walls) {
        prevX = this->getX();
        prevY = this->getY();

        // ga de richting uit
        double dx = 0.f, dy = 0.f;
        if (direction == directions::RIGHT) dx = 0.2f;
        else if (direction == directions::LEFT) dx = -0.2f;
        else if (direction == directions::UP) dy = 2.f / 7.f;
        else if (direction == directions::DOWN) dy = -2.f / 7.f;

        // Positie updaten
        x += deltaTime * dx * speed;
        y += deltaTime * dy * speed;


        // zie of de huidige pos niet op een muur staat
        for (std::shared_ptr<entity>& w : walls) {
            if (standsOn(w) ) {
                prevLocation();
                if (!canChoseDir) {
                    direction = LEFT;
                    ghostObserver->notify(notifications::CHANGE_DIRECTION_LEFT);
                    canChoseDir = true;
                } else {
                    this->nextDirection(walls);
                }
                break;
            }
        }

        if (this->possibleDirections(walls).size() > 2 && canChoseDir) {
            this->nextDirection(walls);
        }



        ghostObserver->notify(notifications::CHANGE_POSITION);
    }

    void redGhost::nextDirection(std::vector<std::shared_ptr<entity>>& walls) {

        prevDirection = this->direction;
        std::vector<directions> possibleDirections = this->possibleDirections(walls);


        if (possibleDirections.empty()) {
            return;
        }

        int chosenDir = random::getInstance()->getNumber(0, possibleDirections.size());

        direction = possibleDirections[chosenDir];
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
} // logic