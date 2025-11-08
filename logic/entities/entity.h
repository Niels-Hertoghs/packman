//
// Created by niels on 11/5/25.
//

#ifndef PACKMAN_ENTITY_H
#define PACKMAN_ENTITY_H

class Render;
/**
 * class entity
 * brief Abstract class of all items/entities that are in the game
 */
class entity {
protected:
    float x;
    float y;
public:
    entity(float x, float y);
    virtual void render(Render* render) = 0;

    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
};



/**
 * class wall
 * brief represents a wall in the map
 */
class wall : public entity {
public:
    wall(float x,float y);
    void render(Render* render);
};



#endif //PACKMAN_ENTITY_H