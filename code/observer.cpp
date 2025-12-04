//
// Created by niels_hertoghs on 11/10/25.
//

#include "observer.h"

#include <iostream>

class camera;

namespace view {
    Observer::Observer(sf::RenderWindow& window,camera& camera)
        : window(window), _camera(camera) {}
}



