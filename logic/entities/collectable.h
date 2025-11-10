//
// Created by niels on 11/6/25.
//

#ifndef PACKMAN_COLLECTABLE_H
#define PACKMAN_COLLECTABLE_H
#include "entity.h"

class Render;

/**
 * class collectable
 * brief An abstract class for the collectables.
 */
class collectable : public entity {
private:
     float points; /// hoeveel points er bij de score worden toegevoegd als het object na 1 seconde wordt opgegeten
     // float size;
public:
     // constructor
     collectable(float x, float y,float points);

     // pure virtual
     virtual void render(std::shared_ptr<Render> render) override = 0;

     // methods
     float getPoints();
     void setPoints(float newPoints);
};

/**
 * class coin
 * brief A concrete class for the coins.
 */
class coin : public collectable {

public:
     coin(float x, float y, float points);
     void render(std::shared_ptr<Render> render) override;
};

class fruit : public collectable {
public:
     fruit(float x, float y, float points);
     void render(std::shared_ptr<Render> render) override;
};

#endif //PACKMAN_COLLECTABLE_H