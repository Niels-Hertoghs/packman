//
// Created by niels_hertoghs on 11/17/25.
//

#include "Ghost.h"

namespace logic {

    /// ---------------------------------------------------------------------------------------------------------------
    /// @class ghost
    /// ---------------------------------------------------------------------------------------------------------------

    Ghost::Ghost(double x, double y) : movableEntity(x,y,0.95f,directions::UP), canChoseDir(false) {}

    std::vector<directions> Ghost::possibleDirections(std::vector<std::shared_ptr<entity>>& walls) {
        std::vector<directions> possibleDirections;

        for (directions dir : {UP, DOWN, RIGHT, LEFT}) {
            double newX = x;
            double newY = y;

            double stepX = 0.f, stepY = 0.f;

            if (dir == directions::RIGHT) stepX = 1/80.f;
            else if (dir == directions::LEFT) stepX = -1/80.f;
            else if (dir == directions::UP) stepY = 1.f / 56.f;
            else if (dir == directions::DOWN) stepY = -1.f / 56.f;
            newX = x + stepX;
            newY = y + stepY;

            bool canMove = std::none_of(walls.begin(), walls.end(),
                [&](const std::shared_ptr<entity>& w) { return wouldCollide(w, newX, newY); });

            if (!canMove) {
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


        if (this->possibleDirections(walls).size() > 2 && canChoseDir) {
            directions dir = this->direction;
            this->nextDirection(walls);
            while (direction == oppositeDirection(dir)) {
                this->possibleDirections(walls);
            }

        }

        // zie of de huidige pos niet op een muur staat
        for (std::shared_ptr<entity>& w : walls) {
            if (standsOn(w)) {
                this->nextDirection(walls);
                canChoseDir = true;
                prevLocation();
                break;
            }
        }
        ghostObserver->notify(notifications::CHANGE_POSITION);
    }

    void redGhost::nextDirection(std::vector<std::shared_ptr<entity>>& walls) {

        prevDirection = this->direction;
        std::vector<directions> possibleDirections = this->possibleDirections(walls);


        int chosenDir = random::getInstance()->getNumber(0, possibleDirections.size());


        direction = possibleDirections[chosenDir];
        if (direction == directions::RIGHT) {
            ghostObserver->notify(notifications::CHANGE_DIRECTION_RIGHT);
        } else if (direction == directions::LEFT) {
            ghostObserver->notify(notifications::CHANGE_DIRECTION_LEFT);
        } else if (direction == directions::UP) {
            ghostObserver->notify(notifications::CHANGE_DIRECTION_UP);
        } else {
            ghostObserver->notify(notifications::CHANGE_DIRECTION_DOWN);
        }

    }



} // logic