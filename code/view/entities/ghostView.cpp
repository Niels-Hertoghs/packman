//
// Created by niels_hertoghs on 11/17/25.
//

#include "ghostView.h"
#include "../../logic/entities/Ghost.h"

namespace view {
ghostView::ghostView(sf::RenderWindow& window, camera& cam, double x, double y,
                     const std::vector<std::pair<int, int>>& spriteCo,
                     const std::vector<std::vector<std::pair<int, int>>>& allSprites)
    : movableEntityView(window, cam, x, y, spriteCo, 2, allSprites) {
}

bool ghostView::isGhost() {
    return true;
}

redGhostView::redGhostView(sf::RenderWindow& window, camera& cam, double x, double y)
    : ghostView(window, cam, x, y, {{-5, 300}, {-5, 350}},
                {
                    {{-5, 100}, {-5, 150}},
                    {{-5, 300}, {-5, 350}},
                    {{-5, 0}, {-5, 50}},
                    {{-5, 200}, {-5, 250}}
                }) {
}


blueGhostView::blueGhostView(sf::RenderWindow& window, camera& cam, double x, double y)
    : ghostView(window, cam, x, y, {{95, 300}, {95, 350}},
                {
                    {{95, 100}, {95, 150}},
                    {{95, 300}, {95, 350}},
                    {{95, 0}, {95, 50}},
                    {{95, 200}, {95, 250}}
                }) {
}


greenGhostView::greenGhostView(sf::RenderWindow& window, camera& cam, double x, double y)
    : ghostView(window, cam, x, y, {{195, 0}, {195, 50}},
                {
                    {{195, 100}, {195, 150}},
                    {{195, 300}, {195, 350}},
                    {{195, 0}, {195, 50}},
                    {{195, 200}, {195, 250}}
                }) {
}


orangeGhostView::orangeGhostView(sf::RenderWindow& window, camera& cam, double x, double y)
    : ghostView(window, cam, x, y, {{145, 200}, {145, 250}},
                {
                    {{145, 100}, {145, 150}},
                    {{145, 300}, {145, 350}},
                    {{145, 0}, {145, 50}},
                    {{145, 200}, {145, 250}}
                }) {
}
} // view
