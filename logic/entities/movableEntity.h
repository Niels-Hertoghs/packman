//
// Created by niels on 11/6/25.
//

#ifndef PACKMAN_MOVABLEENTITY_H
#define PACKMAN_MOVABLEENTITY_H
#include <string>
#include <vector>

#include "entity.h"

class Render;


/**
 * Class movableEntity
 * brief Abstacte klasse voor de beweegbare objecten.
 */
class movableEntity : public entity {
protected:
    std::string direction; /// Richting dat het object gaat.
    float speed; /// De snelheid van het object.
    float prevX, prevY; /// Vorige posities van de objecten (voor de update, als het op een muur gaat staan kan het terug naar de oude positie gaan).
public:
    // constructor
    movableEntity(float x,float y,float speed);

    // pure virutal
    virtual void render(std::shared_ptr<Render> render) override = 0;
    virtual void update(float deltaTime,std::vector<std::shared_ptr<wall>>& walls) = 0;

    // methodes
    bool wouldCollide(const std::shared_ptr<entity>& other, float newX, float newY);
    bool standsOn(const std::shared_ptr<entity>& other);
    void prevLocation();
};

/**
 * Class Packman
 * brief Het Packman object.De concrete klasse.
 */
class Packman : public movableEntity {
private:
    std::string nextDirection; /// Volgende richting zodra mogelijk.
public:
    // constructor
    Packman(float x,float y);

    // methodes
    void render(std::shared_ptr<Render> render) override;
    void update(float deltaTime,std::vector<std::shared_ptr<wall>>& walls) override;


    bool standsOnCoin(const std::shared_ptr<entity>& other);
    void updateDir(const std::string& direction);
};

 // class Ghost : public movableEntity {
 //
 // };




#endif //PACKMAN_MOVABLEENTITY_H