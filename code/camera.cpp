//
// Created by niels-hertoghs on 11/4/25.
//

#include "camera.h"
#include <cmath>

camera::camera(unsigned int w, unsigned int h) : height(h), width(w) {}

std::pair<int, int> camera::worldToPixel(const double &x, const double &y) const {
    int pixelX = ((x + 1.f)/ 2.f) * width;
    int pixelY = ((-y + 1.f)/ 2.f) * height;
    return {pixelX, pixelY};
}

void camera::setDimensions(unsigned int w, unsigned int h) {
    width = w;
    height = h;
}

int camera::distanceToPixelsHeight(const double& distance) const {
    return std::round((distance)/2 * height) + 1; // +1 om de ruimte te dichten tussen de entities
}

int camera::distanceToPixelsWidth(const double& distance) const {
    return std::round((distance)/2 * width) + 1; // +1 om de ruimte te dichten tussen de entities
}