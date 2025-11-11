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
    double x; /// Positie op de x as.
    double y; /// Positie op de y as.
public:
    // constructor
    entity(double x, double y);

    // pure virtual
    virtual void render(std::shared_ptr<Render> render) = 0;

    // methodes
    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;

    virtual ~entity() = default;
};



/**
 * @class wall
 * @brief Concrete klasse die een muur representeert.
 */
class wall : public entity {
public:
    wall(double x,double y);
    void render(std::shared_ptr<Render> render);
};



#endif //PACKMAN_ENTITY_H