//
// Created by niels_hertoghs on 11/17/25.
//

#ifndef PACKMAN_GHOST_H
#define PACKMAN_GHOST_H
#include "movableEntity.h"
#include "../../view/entities/ghostView.h"
#include "../random.h"

namespace logic {
    /**
    * @Class Ghost
    * @brief De abstracte klasse voor alle ghosts.
    */
    class Ghost : public movableEntity {
        int points; /// Het aantal points dat er bij de score komen als er een ghost opgegeten wordt.
    protected:
        enum modes mode;  /// De mode van de Ghost (FEAR_MODE of CHASING_MODE).
        directions prevDirection; /// De vorige richting van de ghost.
        bool hasChosenAtIntersection; /// Zodat die niet meerdere keren kan kiezen aan een intersectie, als die juist heeft gekozen kan die niet meer kiezen tot die voorbij het kruispunt is.
        bool canChoseDir;/// Moet in het begin even de top raken, voordat het de random richtingen uit kan gaan. Is er ook zodat de ghost de ghost kamer kan verlaten en daarna niet meer door de invisible walls kan.
        bool outsideCage; /// Of de ghost al uit de cage is, is voor de ghosts aan de zijde van de cage, die moeten eerste zijwaarts bewegen en dan zoals de andere 2 omhoog..
        bool originalOutsideCage; /// Als de ghost word her spawned moet die terug uit hun cage kunnen (de zijwaartse beweging).
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
        Ghost(double x,double y, bool outsideCage,directions direction,double speed,int points);

        // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
        void update(double deltaTime,std::vector<std::shared_ptr<entity>>& walls) override;
        void died() override;

        // pure virtual methodes
        /**
         * @brief Als de ghost aan een kruispunt staat, kies dan een nieuwe richting.
         * @param walls De muren in de wereld, om te zien dat de ghost er niet door kan bewegen.
         */
        virtual void chooseAtIntersection(std::vector<std::shared_ptr<entity>>& walls) = 0;

        /**
         * @brief Kies de volgende richting van de ghost.
         * @param walls De muren in de wereld, om te zien dat de ghost er niet door kan bewegen.
         */
        virtual void nextDirection(std::vector<std::shared_ptr<entity>>& walls) = 0;

        /**
         * @brief Zien of de ghost mag bewegen (na de start van de game, sommige ghosts moeten even wachten).
         * @return Of de ghost mag bewegen.
         */
        virtual bool canMove() = 0;


        // methodes
        /**
         * @brief Berekent alle mogelijke richtingen waar de ghost naartoe kan bewegen.
         * @param walls De muren in de wereld, om te zien dat de ghost er niet door kan bewegen.
         * @return Vector met alle mogelijke richtingen waar de ghost naartoe kan bewegen.
         */
        [[nodiscard]] std::vector<directions> possibleDirections(const std::vector<std::shared_ptr<entity>>& walls) const;

        /**
         * @return Bool of de ghost al uit de cage is.
         */
        [[nodiscard]] bool hadFirstCollision() const;

        /**
         * @brief Verandert de richting van de ghost en laat de observer weten dat de richting is veranderd.
         * @param direction De richting waar de ghost naartoe moet veranderen.
         */
        void changeDirection(directions direction);

        /**
         * @brief Zet de ghost in fear mode, met alle gevolgen.
         */
        void startFearMode();

        /**
         * @brief Zet de ghost in chase mode, met alle gevolgen.
         */
        void startChaseMode();

        /**
         * @return Het aantal punten dat de ghost waard is als die opgegeten wordt.
         */
        [[nodiscard]] int getGhostPoints() const;

        /**
         * @return De huidige mode van de ghost (FEAR_MODE of CHASING_MODE).
         */
        [[nodiscard]] enum modes get_mode() const;

        /**
         * @brief default destructor.
         */
        ~Ghost() override = default;
    };

    /**
     * @class redGhost
     * @brief De concrete klasse voor de rode ghost (random ghost).
     */
    class redGhost final : public Ghost {
    public:
        // constructor
        /**
         * @param x De positie van de Ghost op de x-as (relatief tussen -1 en 1).
         * @param y De positie van de Ghost op de y-as (relatief tussen -1 en 1).
         * @param speed De snelheid van de ghost.
         * @param points Het aantal punten dat er bij de score komen als de ghost wordt opgegeten.
         */
        redGhost(double x,double y,double speed,int points);

        // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
        void nextDirection(std::vector<std::shared_ptr<entity>>& walls) override;
        [[nodiscard]] bool canMove() override;
        void chooseAtIntersection(std::vector<std::shared_ptr<entity>>& walls) override;

        /**
        * @brief default destructor.
        */
        ~redGhost() override = default;
    };


} // logic

#endif //PACKMAN_GHOST_H