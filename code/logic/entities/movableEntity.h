//
// Created by niels on 11/6/25.
//

#ifndef PACKMAN_MOVABLEENTITY_H
#define PACKMAN_MOVABLEENTITY_H
#include <string>
#include <vector>
#include "../../render/notifications.h"
#include "entity.h"
#include "../../render/movableEntityView.h"

namespace logic {
    class Ghost;
}

namespace logic {
    /**
     * Class movableEntity
     * brief Abstacte klasse voor de beweegbare objecten.
     */
    class movableEntity : public entity {
    protected:
        directions direction; /// Richting dat het object gaat.
        double speed; /// De snelheid van het object.
        double prevX, prevY; /// Vorige posities van de objecten (voor de update, als het op een muur gaat staan kan het terug naar de oude positie gaan).
    public:
        // constructor
        movableEntity(double x,double y,double speed,directions direction);

        // pure virutal
        virtual void update(double deltaTime,std::vector<std::shared_ptr<entity>>& walls) = 0;

        // methodes
        bool wouldCollide(const std::shared_ptr<entity>& other, double newX, double newY);
        bool standsOn(const std::shared_ptr<entity>& other);
        bool pointInWall(std::shared_ptr<entity> wall,double x,double y);
        void prevLocation();

        static directions oppositeDirection(directions dir);
    };

    /**
     * Class Packman
     * brief Het Packman object.De concrete klasse.
     */
    class Packman : public movableEntity {
    private:
        directions nextDirection; /// Volgende richting zodra mogelijk.
        std::shared_ptr<view::packmanView> packmanObserver; /// Pointer naar de observer van pacman.
    public:
        // constructor
        Packman(double x,double y);

        // methodes
        void update(double deltaTime,std::vector<std::shared_ptr<entity>>& walls) override;


        bool standsOnCoin(const std::shared_ptr<entity>& other);
        void updateDir(enum directions);

        void pacmanSubscribe(std::shared_ptr<view::packmanView> pacmanObserver);
        bool standsOnGhost(std::shared_ptr<Ghost> ghost);
    };

}


#endif //PACKMAN_MOVABLEENTITY_H