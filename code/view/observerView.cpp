//
// Created by niels_hertoghs on 12/14/25.
//

#include "observerView.h"

class camera;

namespace view {
ObserverView::ObserverView(sf::RenderWindow& window,camera& camera)
    : window(window), _camera(camera) {}
}