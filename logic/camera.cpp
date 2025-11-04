//
// Created by niels-hertoghs on 11/4/25.
//

#include "camera.h"

camera::camera(unsigned int w, unsigned int h) : height(h), width(w) {}

std::pair<int, int> camera::worldToPixel(const float &x, const float &y) const {
    int pixelX = static_cast<int>(((x+1)/2) * width);
    int pixelY = static_cast<int>(((-y+1)/2) * height);
    return {pixelX, pixelY};
}

void camera::setDimensions(unsigned int w, unsigned int h) {
    width = w;
    height = h;
}