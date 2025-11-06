//
// Created by niels on 11/5/25.
//

#ifndef PACKMAN_RENDER_H
#define PACKMAN_RENDER_H
#include <SFML/Graphics.hpp>
#include "state_maneger/stateManeger.h"
#include "camera.h"
#include "entities/entity.h"

/**
 * class render
 * brief Laadt de sprites in uit een afbeelding, verandert de sprites om de x aantal tijd.
 * Weet  niets van de logica van het item
 */
class Render {
public:
    camera cam;
    std::vector<sf::RectangleShape> sprites;
    std::vector<sf::CircleShape> coins;
    std::vector<sf::Text> text;
public:
    explicit Render(const camera &cam)
        : cam(cam) {
    }

    void loadMap(const camera& camera,const sf::Font& fontF);
    void addWall(float x,float y);
    void addCoin(float x,float y);

};


#endif //PACKMAN_RENDER_H