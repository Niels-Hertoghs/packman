//
// Created by niels-hertoghs on 11/4/25.
//

#ifndef PACKMAN_CAMERA_H
#define PACKMAN_CAMERA_H
#include <utility>

namespace view {
    /**
     * Class camera
     * brief Zorgt ervoor dat elk object/tekst op de juiste plaatst staat op de window, onafhankelijk van de resolutie grote van de window
     */
    class   camera {
    private:
        unsigned int width; /// Breedte van de window in het aantal pixels.
        unsigned int height; /// Hoogte van de window in het aantal pixels.
    public:
        camera(unsigned int w, unsigned int h);

        [[nodiscard]] std::pair<int,int> worldToPixel(const double& width, const double& height) const;
        [[nodiscard]] int distanceToPixelsHeight(const double& distance) const;
        [[nodiscard]] int distanceToPixelsWidth(const double& distance) const;
        void setDimensions(unsigned int w, unsigned int h);
    };
}
#endif //PACKMAN_CAMERA_H