//
// Created by niels-hertoghs on 11/4/25.
//

#ifndef PACKMAN_CAMERA_H
#define PACKMAN_CAMERA_H
#include <utility>

/**
 * class camera
 * brief Makes sure that every object is at the right place on the screen, regardless of the screen resolution
 */
class camera {
private:
    unsigned int width; /// amount of pixels in width
    unsigned int height; /// amount of pixels in height
public:
    camera(unsigned int w, unsigned int h);

    [[nodiscard]] std::pair<int,int> worldToPixel(const float& width, const float& height) const;
    void setDimensions(unsigned int w, unsigned int h);
};

#endif //PACKMAN_CAMERA_H