//
// Created by niels on 11/6/25.
//

#ifndef PACKMAN_MOVABLEENTITY_H
#define PACKMAN_MOVABLEENTITY_H
#include <string>
#include <vector>

#include "entity.h"

class Render;

class movableEntity : public entity {
protected:
    std::string direction;
    float speed;
    float prevX, prevY;
 public:
     movableEntity(float x,float y,float speed);
     virtual void render(std::shared_ptr<Render> render) override = 0;

    bool wouldCollide(const std::shared_ptr<entity>& other, float newX, float newY);
    bool standsOn(const std::shared_ptr<entity>& other);

 };

class Packman : public movableEntity {
private:
    std::string prevDirection;
    std::string nextDirection;
public:
    Packman(float x,float y);
    void render(std::shared_ptr<Render> render) override;

    void update(float deltaTime,std::vector<std::shared_ptr<wall>>& walls);
    void updateDir(const std::string& direction);
    void prevLocation();

};

 // class Ghost : public movableEntity {
 //
 // };




#endif //PACKMAN_MOVABLEENTITY_H