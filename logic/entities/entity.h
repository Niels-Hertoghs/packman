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
private:
    float x;
    float y;
public:
    entity(float x, float y);

    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
};


/// in een ander map zetten
// class movableEntity : public entity {
//PRIVATE:
// std::string direction;
//
// };
// class Ghost : public movableEntity {
//
// };
//
// class Packman : public movableEntity {
//
// };

/**
 * class wall
 * brief represents a wall in the map
 */
class wall : public entity {
public:
    wall(float x,float y);
    void render(Render* render);
};


/// in een andere file zetten
// class collectable : public entity {
// private:
//  float size;
//
// };
//
// class coin : public collectable {
// };
//
// class fruit : public collectable {
//
// };




#endif //PACKMAN_ENTITY_H