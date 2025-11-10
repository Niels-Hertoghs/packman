//
// Created by niels on 11/5/25.
//

#ifndef PACKMAN_RENDER_H
#define PACKMAN_RENDER_H
#include <SFML/Graphics.hpp>
#include "state_maneger/stateManeger.h"
#include "camera.h"
#include "observer.h"
#include "entities/entity.h"
#include "entities/movableEntity.h"

/**
 * class render
 * brief Laadt de sprites in uit een afbeelding, verandert de sprites om de x aantal tijd.
 * Weet  niets van de logica van het item
 */
class Render {
public:
    camera cam;
    sf::Texture texture;
    std::vector<sf::RectangleShape> sprites;
    std::vector<sf::CircleShape> coins;
    std::vector<sf::Text> text;

    std::shared_ptr<Score> score;
public:
    explicit Render(const camera &cam, std::shared_ptr<Score> score);

    void Leveltekst(const camera& camera,const sf::Font& fontF);
    void addWall(float x,float y);
    void addCoin(float x,float y);
    void addFruit(float x,float y);
    void addPackman(float x,float y);
};


#endif //PACKMAN_RENDER_H