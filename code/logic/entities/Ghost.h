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
        bool canChoseDir; /// Moet in het begin even de top raken, voordat het de random richtingen uit kan gaan.
        double dt;
        bool hasChosenAtIntersection; /// zodat die niet meerdere keren kan kiezen aan een intersectie
    public:
        /**
        * @brief Constructor voor de Ghost.
        * @param x De positie van de Ghost op de x-as (relatief tussen -1 en 1).
        * @param y De positie van de Ghost op de y-as (relatief tussen -1 en 1).
        */
        Ghost(double x,double y);

        void update(double deltaTime,std::vector<std::shared_ptr<entity>>& walls) override = 0;
        virtual void nextDirection(std::vector<std::shared_ptr<entity>>& walls) = 0;


        std::vector<directions> possibleDirections(std::vector<std::shared_ptr<entity>>& walls);
    };

    class redGhost : public Ghost {
    private:
        std::shared_ptr<view::redGhostView> ghostObserver; /// Pointer naar de observer van ghost.
    public:
        redGhost(double x,double y);

        /**
        * @brief Initialiseert de observer van de Ghost
        * @param redGhostObserver Pointer naar de observer van Ghost.
        */
        void redGhostSubscribe(std::shared_ptr<view::redGhostView> redGhostObserver);

        void update(double deltaTime, std::vector<std::shared_ptr<entity>>& walls) override;

        // past automatich de direction aan en update observer
        void nextDirection(std::vector<std::shared_ptr<entity>>& walls) override;
    };
} // logic

#endif //PACKMAN_GHOST_H