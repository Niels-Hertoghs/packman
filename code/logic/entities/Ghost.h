//
// Created by niels_hertoghs on 11/17/25.
//

#ifndef PACKMAN_GHOST_H
#define PACKMAN_GHOST_H
#include "movableEntity.h"
#include "../../render/ghostView.h"
#include "../random.h"

namespace logic {
    /**
    * @Class Ghost
    * @brief De abstrcte klasse voor de ghosts.
    */
    class Ghost : public movableEntity {
    protected:
        directions prevDirection;
        enum modes mode;
        bool canChoseDir;/// Moet in het begin even de top raken, voordat het de random richtingen uit kan gaan. Is er ook zodat de ghost de ghost kamer kan verlaten en daarna niet meer door de invisible walls kan.
    public:
        /**
        * @brief Constructor voor de Ghost.
        * @param x De positie van de Ghost op de x-as (relatief tussen -1 en 1).
        * @param y De positie van de Ghost op de y-as (relatief tussen -1 en 1).
        */
        Ghost(double x,double y);

        void update(double deltaTime,std::vector<std::shared_ptr<entity>>& walls) override = 0;
        virtual void nextDirection(std::vector<std::shared_ptr<entity>>& walls) = 0;
        void died() override = 0;

        std::vector<directions> possibleDirections(std::vector<std::shared_ptr<entity>>& walls);
        bool hadFirstCollision();
        void changeDirection(directions direction);
    };

    /**
     * @class redGhost
     */
    class redGhost : public Ghost {
    private:
        std::shared_ptr<view::redGhostView> ghostObserver; /// Pointer naar de observer van ghost.
        bool hasChosenAtIntersection; /// zodat die niet meerdere keren kan kiezen aan een intersectie

    public:
        redGhost(double x,double y);

        /**
        * @brief Initialiseert de observer van de Ghost
        * @param redGhostObserver Pointer naar de observer van Ghost.
        */
        void redGhostSubscribe(std::shared_ptr<view::redGhostView> redGhostObserver);

        void update(double deltaTime, std::vector<std::shared_ptr<entity>>& walls) override;
        void died() override;

        // past automatich de direction aan en update observer
        void nextDirection(std::vector<std::shared_ptr<entity>>& walls) override;
    };

    /**
     * @class blueGhost
     */
    class blueGhost : public Ghost {
    private:
        std::shared_ptr<view::blueGhostView> ghostObserver;
        std::shared_ptr<logic::Packman> pacman;
    public:
        blueGhost(double x,double y);
        void givePacman(std::shared_ptr<logic::Packman> pacman);
        void blueGhostSubscribe(std::shared_ptr<view::blueGhostView>& ghostObserver);
        void update(double deltaTime, std::vector<std::shared_ptr<entity>>& walls) override;
        void died() override;
        void nextDirection(std::vector<std::shared_ptr<entity>>& walls) override;

        static double calculateManhatten(double x1, double y1, double x2, double y2) ;
    };

    /**
     * @class greenGhost
     */
    class greenGhost : public Ghost {
    private:
        std::shared_ptr<view::greenGhostView> ghostObserver;
    public:
        greenGhost(double x,double y);
        void greenGhostSubscribe(std::shared_ptr<view::greenGhostView> ghostObserver);
        void update(double deltaTime, std::vector<std::shared_ptr<entity>>& walls) override;
        void died() override;
        void nextDirection(std::vector<std::shared_ptr<entity>>& walls) override;
    };


    /**
     * @class purpleGhost
     */
    class purpleGhost : public Ghost {
    private:
        std::shared_ptr<view::purpleGhostView> ghostObserver;
    public:
        purpleGhost(double x,double y);
        void purpleGhostSubscribe(std::shared_ptr<view::purpleGhostView> ghostObserver);
        void update(double deltaTime, std::vector<std::shared_ptr<entity>>& walls) override;
        void died() override;
        void nextDirection(std::vector<std::shared_ptr<entity>>& walls) override;
    };
} // logic

#endif //PACKMAN_GHOST_H