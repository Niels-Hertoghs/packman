//
// Created by niels_hertoghs on 11/20/25.
//
#include "make_text.h"
namespace view {
    sf::Text makeText(const sf::Font& fontF, const std::string& text, double charSize, sf::Color color,double x, double y,const camera& cam)
    {
        sf::Text Text;
        Text.setFont(fontF);
        Text.setString(text);
        Text.setCharacterSize(cam.distanceToPixelsHeight(charSize));
        Text.setFillColor(color);

        // Zet origin wél met top en left in aanmerking genomen
        sf::FloatRect bounds = Text.getLocalBounds();
        Text.setOrigin((bounds.left + bounds.width) / 2.f,
                       (bounds.top  + bounds.height) / 2.f);

        // En pas dan pas de positie toe (zodat position refereert aan de nieuwe origin)
        auto Pos = cam.worldToPixel(x, y);
        Text.setPosition(static_cast<float>(Pos.first), static_cast<float>(Pos.second));

        return Text;
    }
}