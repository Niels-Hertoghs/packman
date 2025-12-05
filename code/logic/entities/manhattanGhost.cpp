//
// Created by niels_hertoghs on 11/25/25.
//

#include "manhattanGhost.h"
#include "../Stopwatch.h"

namespace logic {
    /// ---------------------------------------------------------------------------------------------------------------
    /// manhattanGhost
    /// ---------------------------------------------------------------------------------------------------------------

    manhattanGhost::manhattanGhost(double x,double y,bool outsideCage,directions direction,double speed,int points) : Ghost(x,y,outsideCage,direction,speed,points) {}

    void manhattanGhost::givePacman(std::shared_ptr<logic::Pacman> _pacman) {
        pacman = std::move(_pacman);
    }

    double manhattanGhost::calculateManhattan(double x1, double y1, double x2, double y2) {
        double x = std::abs(x1 - x2);
        double y = std::abs(y1 - y2);
        return x + y;
    }


    void manhattanGhost::nextDirection(std::vector<std::shared_ptr<entity>>& walls) {

        std::vector<directions> posDirections = this->possibleDirections(walls);

        // De volg kant van pacman opvargen van de derivdes.
        std::pair<double, double> kantPac = getFollowSide();

        // initializatie om de richting te kiezen
        directions nextDirection = direction;
        double edgeDistance = 0;
        if (mode == CHASING_MODE) {
            edgeDistance = std::numeric_limits<double>::max();
        } else if (mode == FEAR_MODE) {
            edgeDistance = std::numeric_limits<double>::min();
        }


        for (directions d : posDirections) {
            // std::pair<double, double> voorkantGhost = this->getFront(direction);
            // de pos van het spookje als het direction p op gaat
            std::pair<double,double> nextPosGhost = calculateNextPos(1,d,x + 1.f/20.f,y - 1.f/14.f);
            double distance = calculateManhattan(kantPac.first,kantPac.second,nextPosGhost.first,nextPosGhost.second);
            if (mode == CHASING_MODE) {
                // zoek de kleinste distance
                if (distance < edgeDistance) {
                    edgeDistance = distance;
                    nextDirection = d;
                }
            } else if (mode == FEAR_MODE) {
                if (distance > edgeDistance) {
                    // zoek de grootste distance
                    edgeDistance = distance;
                    nextDirection = d;
                }
            }
        }

        changeDirection(nextDirection);

    }

    void manhattanGhost::chooseAtIntersection(std::vector<std::shared_ptr<entity>>& walls) {
        this->nextDirection(walls);
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// frontManhattanGhost
    /// ---------------------------------------------------------------------------------------------------------------

    frontManhattanGhost::frontManhattanGhost(double x, double y,bool outsideCage,directions direction,double speed,int points) : manhattanGhost(x,y,outsideCage,direction,speed,points) {}

    std::pair<double, double> frontManhattanGhost::getFollowSide() {
        std::pair<double, double> voorkantPac = pacman->getFront();
        return voorkantPac;
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// blueGhost
    /// ---------------------------------------------------------------------------------------------------------------


    blueGhost::blueGhost(double x, double y,double speed,int points)  : frontManhattanGhost(x,y,true,UP,speed,points) {}

    bool blueGhost::canMove() {
        return true;
    }




    /// ---------------------------------------------------------------------------------------------------------------
    /// greenGhost
    /// ---------------------------------------------------------------------------------------------------------------


    greenGhost::greenGhost(double x, double y,double speed,int points)  : frontManhattanGhost(x,y,false,RIGHT,speed,points) {}

    bool greenGhost::canMove() {
        return Stopwatch::getInstance()->canStartAfter5Sec();
    }


    /// ---------------------------------------------------------------------------------------------------------------
    /// orangeGhost
    /// ---------------------------------------------------------------------------------------------------------------


    orangeGhost::orangeGhost(double x, double y,double speed,int points)  : manhattanGhost(x,y,false,LEFT,speed,points) {}

    std::pair<double, double> orangeGhost::getFollowSide() {
        return pacman->getBack();
    }

    bool orangeGhost::canMove() {
        return Stopwatch::getInstance()->canStartAfter10Sec();
    }



} // logic