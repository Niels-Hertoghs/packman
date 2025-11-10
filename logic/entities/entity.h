//
// Created by niels on 11/5/25.
//

#ifndef PACKMAN_ENTITY_H
#define PACKMAN_ENTITY_H
#include <memory>

class Render;
/**
 * @class entity
 * @brief Een abstracte klasse voor alle objecten in de game.
 */
class entity {
protected:
    float x; /// Positie op de x as.
    float y; /// Positie op de y as.
public:
    // constructor
    entity(float x, float y);

    // pure virtual
    virtual void render(std::shared_ptr<Render> render) = 0;

    // methodes
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;

    virtual ~entity() = default;
};



/**
 * @class wall
 * @brief Concrete klasse die een muur representeert.
 */
class wall : public entity {
public:
    wall(float x,float y);
    void render(std::shared_ptr<Render> render);
};



#endif //PACKMAN_ENTITY_H