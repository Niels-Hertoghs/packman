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
        enum modes mode;  /// De mode van de Ghost.
        directions prevDirection;
        bool hasChosenAtIntersection; /// zodat die niet meerdere keren kan kiezen aan een intersectie
        bool canChoseDir;/// Moet in het begin even de top raken, voordat het de random richtingen uit kan gaan. Is er ook zodat de ghost de ghost kamer kan verlaten en daarna niet meer door de invisible walls kan.
        bool outsideCage; /// Of de ghost al uit de cage is

        bool originalOutsideCage; /// als de ghost woordt her spawned moet die terug uit zijn kot kunnen.
    public:
        /**
        * @brief Constructor voor de Ghost.
        * @param x De positie van de Ghost op de x-as (relatief tussen -1 en 1).
        * @param y De positie van de Ghost op de y-as (relatief tussen -1 en 1).
        */
        Ghost(double x,double y, bool outsideCage,directions direction,double speed);

        void update(double deltaTime,std::vector<std::shared_ptr<entity>>& walls) override;

        virtual void chooseAtIntersection(std::vector<std::shared_ptr<entity>>& walls) = 0;
        virtual void nextDirection(std::vector<std::shared_ptr<entity>>& walls) = 0;
        virtual bool canMove() = 0;

        std::vector<directions> possibleDirections(std::vector<std::shared_ptr<entity>>& walls);
        [[nodiscard]] bool hadFirstCollision() const;
        void changeDirection(directions direction);
        void startFearMode();
        void died() override;

    };

    /**
     * @class redGhost
     */
    class redGhost : public Ghost {
    private:

    public:
        redGhost(double x,double y,double speed);

        /**
        * @brief Initialiseert de observer van de Ghost
        * @param redGhostObserver Pointer naar de observer van Ghost.
        */
        void redGhostSubscribe(const std::shared_ptr<view::redGhostView>& redGhostObserver);


        // past automatich de direction aan en update observer
        void nextDirection(std::vector<std::shared_ptr<entity>>& walls) override;
        bool canMove() override;
        void chooseAtIntersection(std::vector<std::shared_ptr<entity>>& walls) override;
    };


} // logic

#endif //PACKMAN_GHOST_H