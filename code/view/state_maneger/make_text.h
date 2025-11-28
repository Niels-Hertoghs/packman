//
// Created by niels_hertoghs on 11/20/25.
//


#include <SFML/Graphics.hpp>
#include "../camera.h"

namespace view {
    sf::Text makeText(const sf::Font& fontF, const std::string& text, double charSize, sf::Color color,double x, double y,const camera& cam);

    /**
     * origin = mid
     */
    sf::RectangleShape makeButton(float height, float width, sf::Color kleur,const camera& cam,float x, float y);
}
