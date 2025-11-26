//
// Created by niels_hertoghs on 11/25/25.
//

#ifndef PACKMAN_MANHATTENGHOST_H
#define PACKMAN_MANHATTENGHOST_H
#include "Ghost.h"

namespace logic {
    /**
    * @class manhattenGhost
    */
    class manhattenGhost : public Ghost {
    protected:
        std::shared_ptr<logic::Packman> pacman;
    public:
        manhattenGhost(double x,double y);
        void givePacman(std::shared_ptr<logic::Packman> pacman);
        static double calculateManhatten(double x1, double y1, double x2, double y2) ;

        void nextDirection(std::vector<std::shared_ptr<entity>>& walls) override;
        void chooseAtIntersection(std::vector<std::shared_ptr<entity>>& walls) override;

        virtual std::pair<double, double> getFollowSide() = 0;
        bool canMove() override = 0;
    };

    /**
    * @class frontManhattenGhost
    */
    class frontManhattenGhost : public manhattenGhost {
    public:
        frontManhattenGhost(double x,double y);

        std::pair<double, double> getFollowSide() override;
        bool canMove() override = 0;
    };

    /**
     * @class blueGhost
     */
    class blueGhost : public frontManhattenGhost {

    public:
        blueGhost(double x,double y);
        void blueGhostSubscribe(const std::shared_ptr<view::blueGhostView>& ghostObserver);
        bool canMove() override;
    };

    /**
     * @class greenGhost
     */
    class greenGhost : public frontManhattenGhost {
    public:
        greenGhost(double x,double y);
        void greenGhostSubscribe(std::shared_ptr<view::greenGhostView> ghostObserver);
        bool canMove() override;
    };


    /**
     * @class orangeGhost
     */
    class orangeGhost : public manhattenGhost {
    private:
    public:
        orangeGhost(double x,double y);
        void purpleGhostSubscribe(std::shared_ptr<view::orangeGhostView> ghostObserver);
        std::pair<double, double> getFollowSide() override;
        bool canMove() override;
    };
} // logic

#endif //PACKMAN_MANHATTENGHOST_H