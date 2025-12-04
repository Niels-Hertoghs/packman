//
// Created by niels_hertoghs on 11/20/25.
//
#include "make_text.h"
namespace view {
    sf::Text makeText(const sf::Font& fontF, const std::string& text, const double charSize, const sf::Color color, const double x, const double y,const camera& cam)
    {
        sf::Text Text;
        Text.setFont(fontF);
        Text.setString(text);
        Text.setCharacterSize(cam.distanceToPixelsHeight(charSize));
        Text.setFillColor(color);

        // Zet origin wél met top en left in aanmerking genomen
        const sf::FloatRect bounds = Text.getLocalBounds();
        Text.setOrigin((bounds.left + bounds.width) / 2.f,
                       (bounds.top  + bounds.height) / 2.f);

        // En pas dan pas de positie toe (zodat position refereert aan de nieuwe origin)
        auto [fst, snd] = cam.worldToPixel(x, y);
        Text.setPosition(static_cast<float>(fst), static_cast<float>(snd));

        return Text;
    }

    sf::RectangleShape makeButton(const float height, const float width, const sf::Color kleur, const camera& cam, const float x, const float y) {
        const int buttonHeight = cam.distanceToPixelsHeight(height);
        const int buttonWidth = cam.distanceToPixelsWidth(width);
        sf::RectangleShape button(sf::Vector2f(static_cast<float>(buttonWidth),static_cast<float>(buttonHeight)));
        button.setFillColor(kleur);

        const sf::FloatRect boundsRect =  button.getLocalBounds();
        button.setOrigin(boundsRect.width / 2.f, boundsRect.height / 2.f);
        auto [fst, snd] = cam.worldToPixel(x,y);
        button.setPosition(static_cast<float>(fst), static_cast<float>(snd));

        return button;
    }

}