//
// Created by niels_hertoghs on 11/25/25.
//

#include "manhattenGhost.h"

namespace logic {
    /// ---------------------------------------------------------------------------------------------------------------
    /// manhattenGhost
    /// ---------------------------------------------------------------------------------------------------------------

    manhattenGhost::manhattenGhost(double x,double y,bool outsideCage,directions direction,double speed) : Ghost(x,y,outsideCage,direction,speed) {}

    void manhattenGhost::givePacman(std::shared_ptr<logic::Packman> _pacman) {
        pacman = std::move(_pacman);
    }

    double manhattenGhost::calculateManhatten(double x1, double y1, double x2, double y2) {
        double x = std::abs(x1 - x2);
        double y = std::abs(y1 - y2);
        return x + y;
    }


    void manhattenGhost::nextDirection(std::vector<std::shared_ptr<entity>>& walls) {

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
            double distance = calculateManhatten(kantPac.first,kantPac.second,nextPosGhost.first,nextPosGhost.second);
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

    void manhattenGhost::chooseAtIntersection(std::vector<std::shared_ptr<entity>>& walls) {
        this->nextDirection(walls);
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// frontManhattenGhost
    /// ---------------------------------------------------------------------------------------------------------------

    frontManhattenGhost::frontManhattenGhost(double x, double y,bool outsideCage,directions direction,double speed) : manhattenGhost(x,y,outsideCage,direction,speed) {}

    std::pair<double, double> frontManhattenGhost::getFollowSide() {
        std::pair<double, double> voorkantPac = pacman->getFront();
        return voorkantPac;
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// blueGhost
    /// ---------------------------------------------------------------------------------------------------------------


    blueGhost::blueGhost(double x, double y,double speed)  : frontManhattenGhost(x,y,true,UP,speed) {}


    void blueGhost::blueGhostSubscribe(const std::shared_ptr<view::blueGhostView>& _ghostObserver) {
        observer = _ghostObserver;
    }

    bool blueGhost::canMove() {
        return true;
    }




    /// ---------------------------------------------------------------------------------------------------------------
    /// greenGhost
    /// ---------------------------------------------------------------------------------------------------------------


    greenGhost::greenGhost(double x, double y,double speed)  : frontManhattenGhost(x,y,false,RIGHT,speed) {}

    void greenGhost::greenGhostSubscribe(std::shared_ptr<view::greenGhostView> _ghostObserver) {
        observer = std::move(_ghostObserver);
    }

    bool greenGhost::canMove() {
        return Stopwatch::getInstance()->canStartAfter5Sec();
    }


    /// ---------------------------------------------------------------------------------------------------------------
    /// orangeGhost
    /// ---------------------------------------------------------------------------------------------------------------


    orangeGhost::orangeGhost(double x, double y,double speed)  : manhattenGhost(x,y,false,LEFT,speed) {}

    void orangeGhost::orangeGhostSubscribe(std::shared_ptr<view::orangeGhostView> _ghostObserver) {
        observer = std::move(_ghostObserver);
    }

    std::pair<double, double> orangeGhost::getFollowSide() {
        return pacman->getBack();
    }

    bool orangeGhost::canMove() {
        return Stopwatch::getInstance()->canStartAfter10Sec();
    }



} // logic