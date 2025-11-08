//
// Created by niels on 11/6/25.
//

#ifndef PACKMAN_MOVABLEENTITY_H
#define PACKMAN_MOVABLEENTITY_H
#include <string>
#include "entity.h"

class Render;

class movableEntity : public entity {
private:
     std::string direction;
 public:
     movableEntity(float x,float y);
     virtual void render(Render *render) override = 0;

 };

class Packman : public movableEntity {
public:
    Packman(float x,float y);
    void render(Render *render) override;

    void update(float deltaTime);
};

 // class Ghost : public movableEntity {
 //
 // };




#endif //PACKMAN_MOVABLEENTITY_H