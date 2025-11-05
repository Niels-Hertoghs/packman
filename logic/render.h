//
// Created by niels on 11/5/25.
//

#ifndef PACKMAN_RENDER_H
#define PACKMAN_RENDER_H
#include <SFML/Graphics.hpp>
#include "state_maneger/stateManeger.h"
#include "camera.h"

/**
 * class render
 * brief Laadt de sprites in uit een afbeelding, verandert de sprites om de x aantal tijd.
 * Weet  niets van de logica van het item
 */
class Render {
public:
    Render();
    std::pair<std::vector<sf::RectangleShape>,std::vector<sf::Text>> loadMap(const camera& camera,const sf::Font& fontF);

};


#endif //PACKMAN_RENDER_H