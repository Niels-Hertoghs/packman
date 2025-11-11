//
// Created by niels on 11/6/25.
//

#ifndef PACKMAN_COLLECTABLE_H
#define PACKMAN_COLLECTABLE_H
#include "entity.h"

class Render;

/**
 * @class collectable
 * @brief Een abstracte klasse voor collectables.
 */
class collectable : public entity {
private:
     double points; /// Hoeveel punten er bij de score worden toegevoegd als het object na 1 seconde wordt opgegeten.
public:
     // constructor
     collectable(double x, double y,double points);

     // pure virtual
     virtual void render(std::shared_ptr<Render> render) override = 0;

     // methods
     double getPoints();
     void setPoints(double newPoints);
};

/**
 * @class coin
 * @brief Een concrete klasse voor de coins.
 */
class coin : public collectable {

public:
     coin(double x, double y, double points);
     void render(std::shared_ptr<Render> render) override;
};

class fruit : public collectable {
public:
     fruit(double x, double y, double points);
     void render(std::shared_ptr<Render> render) override;
};

#endif //PACKMAN_COLLECTABLE_H