//
// Created by niels_hertoghs on 11/20/25.
//


#include <SFML/Graphics/Text.hpp>
#include "../../camera.h"

namespace view {
    sf::Text makeText(const sf::Font& fontF, const std::string& text, double charSize, sf::Color color,double x, double y,const camera& cam);
}
