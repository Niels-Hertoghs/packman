//
// Created by niels-hertoghs on 11/4/25.
//

#include "camera.h"
#include <cmath>

namespace view {
camera::camera(const unsigned int w, const unsigned int h)
    : width(w), height(h) {
}

std::pair<int, int> camera::worldToPixel(const double& x, const double& y) const {
    int pixelX = static_cast<int>(((x + 1.f) / 2.f) * width);
    int pixelY = static_cast<int>(((-y + 1.f) / 2.f) * height);
    return {pixelX, pixelY};
}

void camera::setDimensions(const unsigned int w, const unsigned int h) {
    width = w;
    height = h;
}

int camera::distanceToPixelsHeight(const double& distance) const {
    return static_cast<int>(std::round((distance) / 2 * height) + 1);
    // +1 om de ruimte te dichten tussen de entities
}

int camera::distanceToPixelsWidth(const double& distance) const {
    return static_cast<int>(std::round((distance) / 2 * width) + 1);
    // +1 om de ruimte te dichten tussen de entities
}
}
