//
// Created by niels_hertoghs on 11/20/25.
//
#pragma once


#include <SFML/Graphics.hpp>
#include "../camera.h"

namespace view {
    // Hulp functies die repeterende code verminderd.

    /**
     * @brief Maak een sf::Text object met de gegeven parameters.
     * @param fontF Pointer naar het font dat gebruikt moet worden.
     * @param text Text die weergegeven moet worden.
     * @param charSize De karakter grootte in wereld coordinate (hoogte).
     * @param color De kleur van de text.
     * @param x De x positie in wereld coordinate (centrum text).
     * @param y De y positie in wereld coordinate (centrum text).
     * @param cam Camera object voor het omzetten van wereld naar pixel coordinaten.
     * @return Het gemaakte sf::Text object.
     */
    sf::Text makeText(const sf::Font& fontF, const std::string& text, double charSize, sf::Color color,double x, double y,const camera& cam);

    /**
     * @brief Maak een sf::RectangleShape object (button) met de gegeven parameters.
     * @param height De hoogte van de button in wereld coordinate (relatief tussen -1 en 1).
     * @param width De breedte van de button in wereld coordinate.
     * @param kleur De kleur van de button.
     * @param cam Camera object voor het omzetten van wereld naar pixel coordinaten.
     * @param x De x positie in wereld coordinate (centrum button).
     * @param y De y positie in wereld coordinate (centrum button).
     * @return Het gemaakte sf::RectangleShape object.
     */
    sf::RectangleShape makeButton(float height, float width, sf::Color kleur,const camera& cam,float x, float y);
}
