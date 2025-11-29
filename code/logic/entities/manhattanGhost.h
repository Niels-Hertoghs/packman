//
// Created by niels_hertoghs on 11/25/25.
//

#ifndef PACKMAN_MANHATTENGHOST_H
#define PACKMAN_MANHATTENGHOST_H
#include "Ghost.h"

namespace logic {
    /**
    * @class manhattanGhost
    * @brief Abstracte klasse voor ghosts die de manhatten afstand gebruiken om pacman te volgen.
    */
    class manhattanGhost : public Ghost {
    protected:
        std::shared_ptr<Packman> pacman; /// Pointer naar pacman, om zijn positie te weten.
    public:
        // constructor
        /**
         *
         * @param x De positie van de Ghost op de x-as (relatief tussen -1 en 1).
         * @param y De positie van de Ghost op de y-as (relatief tussen -1 en 1).
         * @param outsideCage Of de ghost aan de zijkant van de cage zit, om eerst zijwaarts te bewegen voor het omhoog gaat.
         * @param direction De richting van de ghost.
         * @param speed De snelheid van de ghost.
         * @param points Het aantal punten dat er bij de score komen als de ghost wordt opgegeten.
         */
        manhattanGhost(double x,double y,bool outsideCage,directions direction,double speed,int points);

        // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
        void nextDirection(std::vector<std::shared_ptr<entity>>& walls) override;
        void chooseAtIntersection(std::vector<std::shared_ptr<entity>>& walls) override;
        bool canMove() override = 0;

        /**
         *
         * @param pacman
         */
        void givePacman(std::shared_ptr<logic::Packman> pacman);
        static double calculateManhatten(double x1, double y1, double x2, double y2) ;



        virtual std::pair<double, double> getFollowSide() = 0;
    };

    /**
    * @class frontManhattenGhost
    */
    class frontManhattenGhost : public manhattanGhost {
    public:
        frontManhattenGhost(double x,double y,bool outsideCage,directions direction,double speed,int points);

        std::pair<double, double> getFollowSide() override;
        bool canMove() override = 0;
    };

    /**
     * @class blueGhost
     */
    class blueGhost : public frontManhattenGhost {

    public:
        blueGhost(double x,double y,double speed,int points);
        bool canMove() override;
    };

    /**
     * @class greenGhost
     */
    class greenGhost : public frontManhattenGhost {
    public:
        greenGhost(double x,double y,double speed,int points);
        bool canMove() override;
    };


    /**
     * @class orangeGhost
     */
    class orangeGhost : public manhattanGhost {
    private:
    public:
        orangeGhost(double x,double y,double speed,int points);
        std::pair<double, double> getFollowSide() override;
        bool canMove() override;
    };
} // logic

#endif //PACKMAN_MANHATTENGHOST_H