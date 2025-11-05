//
// Created by niels-hertoghs on 11/4/25.
//

#include "camera.h"

camera::camera(unsigned int w, unsigned int h) : height(h), width(w) {}

std::pair<int, int> camera::worldToPixel(const float &x, const float &y) const {
    float aspect = static_cast<float>(width) / static_cast<float>(height);
    int pixelX = static_cast<int>(((x / aspect + 1.f) / 2.f) * width);
    int pixelY = static_cast<int>(((-y + 1.f) / 2.f) * height);
    return {pixelX, pixelY};
}


void camera::setDimensions(unsigned int w, unsigned int h) {
    width = w;
    height = h;
}

int camera::distanceToPixelsHeight(const float& distance) const {
    return static_cast<int>((distance)/2 * height);
}

int camera::distanceToPixelsWidth(const float& distance) const {
    return static_cast<int>((distance+1)/2 * width);
}