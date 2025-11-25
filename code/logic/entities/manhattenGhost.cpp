//
// Created by niels_hertoghs on 11/25/25.
//

#include "manhattenGhost.h"

namespace logic {
    /// ---------------------------------------------------------------------------------------------------------------
    /// manhattenGhost
    /// ---------------------------------------------------------------------------------------------------------------

    manhattenGhost::manhattenGhost(double x,double y) : Ghost(x,y) {}

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
        double minDistance = std::numeric_limits<double>::max();

        for (directions d : posDirections) {
            // std::pair<double, double> voorkantGhost = this->getFront(direction);
            // de pos van het spookje als het direction p op gaat
            std::pair<double,double> nextPosGhost = calculateNextPos(1,d,x + 1.f/20.f,y - 1.f/14.f);
            double distance = calculateManhatten(kantPac.first,kantPac.second,nextPosGhost.first,nextPosGhost.second);
            if (distance < minDistance) {
                minDistance = distance;
                nextDirection = d;
            }
        }


        changeDirection(nextDirection);

        notifyDir();

    }

    void manhattenGhost::chooseAtIntersection(std::vector<std::shared_ptr<entity>>& walls) {
        this->nextDirection(walls);
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// frontManhattenGhost
    /// ---------------------------------------------------------------------------------------------------------------

    frontManhattenGhost::frontManhattenGhost(double x, double y) : manhattenGhost(x,y) {}

    std::pair<double, double> frontManhattenGhost::getFollowSide() {
        std::pair<double, double> voorkantPac = pacman->getFront();
        return voorkantPac;
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// blueGhost
    /// ---------------------------------------------------------------------------------------------------------------


    blueGhost::blueGhost(double x, double y)  : frontManhattenGhost(x,y) {}


    void blueGhost::blueGhostSubscribe(const std::shared_ptr<view::blueGhostView>& _ghostObserver) {
        observer = _ghostObserver;
    }





    /// ---------------------------------------------------------------------------------------------------------------
    /// greenGhost
    /// ---------------------------------------------------------------------------------------------------------------


    greenGhost::greenGhost(double x, double y)  : frontManhattenGhost(x,y) {}

    void greenGhost::greenGhostSubscribe(std::shared_ptr<view::greenGhostView> _ghostObserver) {
        observer = std::move(_ghostObserver);
    }


    /// ---------------------------------------------------------------------------------------------------------------
    /// purpleGhost
    /// ---------------------------------------------------------------------------------------------------------------


    purpleGhost::purpleGhost(double x, double y)  : manhattenGhost(x,y) {}

    void purpleGhost::purpleGhostSubscribe(std::shared_ptr<view::purpleGhostView> _ghostObserver) {
        observer = std::move(_ghostObserver);
    }

    std::pair<double, double> purpleGhost::getFollowSide() {
        // TODO: veranderen naar back
        return pacman->getFront();
    }


} // logic