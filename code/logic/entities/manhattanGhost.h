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
        std::shared_ptr<Pacman> pacman; /// Pointer naar pacman, om zijn positie te weten.
    public:
        // constructor
        /**
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
        [[nodiscard]] bool canMove() override = 0;
        void givePacman(std::shared_ptr<Pacman> pacman) override;
        ghostTypes getType() override = 0;


        // pure virtual methodes
        /**
         * @brief Haalt de kant van pacman op die de ghost moet volgen (voorkant of achterkant).
         * @return Pair van de x en y coordinaat van de kant van pacman die de ghost moet volgen.
         */
        [[nodiscard]] virtual std::pair<double, double> getFollowSide() = 0;

        /**
         * @brief Berekent de manhattan afstand tussen 2 punten.
         * @param x1 De x coordinaat van het eerste punt.
         * @param y1 De y coordinaat van het eerste punt.
         * @param x2 De x coordinaat van het tweede punt.
         * @param y2 De y coordinaat van het tweede punt.
         * @return De manhattan afstand tussen de 2 punten.
         */
        [[nodiscard]] static double calculateManhattan(double x1, double y1, double x2, double y2) ;

        /**
        * @brief default destructor.
        */
        ~manhattanGhost() override = default;
    };

    /**
    * @class frontManhattanGhost
    * @brief Abstracte klasse voor ghosts die de voorkant van pacman volgen (zijn weg proberen af te snijden).
    */
    class frontManhattanGhost : public manhattanGhost {
    public:
        // constructor
        /**
         * @param x De positie van de Ghost op de x-as (relatief tussen -1 en 1).
         * @param y De positie van de Ghost op de y-as (relatief tussen -1 en 1).
         * @param outsideCage Of de ghost aan de zijkant van de cage zit, om eerst zijwaarts te bewegen voor het omhoog gaat.
         * @param direction De richting van de ghost.
         * @param speed De snelheid van de ghost.
         * @param points Het aantal punten dat er bij de score komen als de ghost wordt opgegeten.
         */
        frontManhattanGhost(double x,double y,bool outsideCage,directions direction,double speed,int points);

        // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
        [[nodiscard]] std::pair<double, double> getFollowSide() override;
        [[nodiscard]] bool canMove() override = 0;
        ghostTypes getType() override = 0;

        /**
        * @brief default destructor.
        */
        ~frontManhattanGhost() override = default;
    };

    /**
     * @class blueGhost
     * @brief De concrete klasse voor de blauwe ghost, die de voorkant van pacman volgt.
     */
    class blueGhost final : public frontManhattanGhost {
    public:
        // constructor
        /**
         * @param x De positie van de Ghost op de x-as (relatief tussen -1 en 1).
         * @param y De positie van de Ghost op de y-as (relatief tussen -1 en 1).
         * @param speed De snelheid van de ghost.
         * @param points Het aantal punten dat er bij de score komen als de ghost wordt opgegeten.
         */
        blueGhost(double x,double y,double speed,int points);

        // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
        [[nodiscard]] bool canMove() override;
        ghostTypes getType() override;

        /**
        * @brief default destructor.
        */
        ~blueGhost() override = default;
    };

    /**
     * @class greenGhost
     * @brief De concrete klasse voor de groene ghost, die de voorkant van pacman volgt.
     */
    class greenGhost final : public frontManhattanGhost {
    public:
        // constructor
        /**
         * @param x De positie van de Ghost op de x-as (relatief tussen -1 en 1).
         * @param y De positie van de Ghost op de y-as (relatief tussen -1 en 1).
         * @param speed De snelheid van de ghost.
         * @param points Het aantal punten dat er bij de score komen als de ghost wordt opgegeten.
         */
        greenGhost(double x,double y,double speed,int points);

        // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
        [[nodiscard]] bool canMove() override;
        ghostTypes getType() override;

        /**
        * @brief default destructor.
        */
        ~greenGhost() override = default;
    };


    /**
     * @class orangeGhost
     * @brief Concrete klasse voor de oranje ghost, die de achterkant van pacman volgt.
     */
    class orangeGhost final : public manhattanGhost {
    public:
        // constructor
        /**
         * @param x De positie van de Ghost op de x-as (relatief tussen -1 en 1).
         * @param y De positie van de Ghost op de y-as (relatief tussen -1 en 1).
         * @param speed De snelheid van de ghost.
         * @param points Het aantal punten dat er bij de score komen als de ghost wordt opgegeten.
         */
        orangeGhost(double x,double y,double speed,int points);

        // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
        std::pair<double, double> getFollowSide() override;
        [[nodiscard]] bool canMove() override;
        ghostTypes getType() override;

        /**
         * @brief default destructor.
         */
        ~orangeGhost() override = default;
    };
} // logic

#endif //PACKMAN_MANHATTENGHOST_H