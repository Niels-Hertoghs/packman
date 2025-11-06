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
     float size;
public:
     collectable(float x, float y);
     virtual void render(Render *render) override = 0;

};

/**
 * class coin
 * brief A concrete class for the coins.
 */
class coin : public collectable {
public:
     coin(float x, float y);
     void render(Render *render) override;
};

class fruit : public collectable {
public:
     fruit(float x, float y);
     void render(Render *render) override;
};

#endif //PACKMAN_COLLECTABLE_H