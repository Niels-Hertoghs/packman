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
    };

    /**
    * @class manhattenGhost
    */
    class frontManhattenGhost : public manhattenGhost {
    public:
        frontManhattenGhost(double x,double y);

        std::pair<double, double> getFollowSide() override;

    };

    /**
     * @class blueGhost
     */
    class blueGhost : public frontManhattenGhost {

    public:
        blueGhost(double x,double y);
        void blueGhostSubscribe(const std::shared_ptr<view::blueGhostView>& ghostObserver);

    };

    /**
     * @class greenGhost
     */
    class greenGhost : public frontManhattenGhost {
    private:
    public:
        greenGhost(double x,double y);
        void greenGhostSubscribe(std::shared_ptr<view::greenGhostView> ghostObserver);

    };


    /**
     * @class purpleGhost
     */
    class purpleGhost : public manhattenGhost {
    private:
    public:
        purpleGhost(double x,double y);
        void purpleGhostSubscribe(std::shared_ptr<view::purpleGhostView> ghostObserver);
        std::pair<double, double> getFollowSide() override;
    };
} // logic

#endif //PACKMAN_MANHATTENGHOST_H