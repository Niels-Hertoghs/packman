//
// Created by niels-hertoghs on 11/4/25.
//

#ifndef PACKMAN_CAMERA_H
#define PACKMAN_CAMERA_H
#include <utility>

namespace view {
/**
 * @Class camera
 * @brief Zorgt ervoor dat elk object/tekst op de juiste plaatst staat op de window, onafhankelijk van de resolutie grote van de window
 */
class camera {
    unsigned int width;  /// Breedte van de window in het aantal pixels.
    unsigned int height; /// Hoogte van de window in het aantal pixels.
public:
    /**
     * @brief Constructor
     * @param w Breedte van de window in pixels.
     * @param h Hoogte van de window in pixels.
     */
    camera(unsigned int w, unsigned int h);

    /**
     * @brief Zet wereld coordinaten om naar pixel coordinaten.
     * @param width De wereld x coordinate (tussen -1 en 1).
     * @param height De wereld y coordinate (tussen -1 en 1).
     * @return Pair van pixel coordinaten (x,y).
     */
    [[nodiscard]] std::pair<int, int> worldToPixel(const double& width, const double& height) const;

    /**
     * @brief Zet een hoogte in wereld coordinaten om naar pixel coordinaten (hoogte).
     * @param distance De hoogte in wereld coordinaten.
     * @return De hoogte in pixel coordinaten.
     */
    [[nodiscard]] int distanceToPixelsHeight(const double& distance) const;

    /**
     * @brief Zet een breedte in wereld coordinaten om naar pixel coordinaten (breedte).
     * @param distance De breedte in wereld coordinaten.
     * @return De breedte in pixel coordinaten.
     */
    [[nodiscard]] int distanceToPixelsWidth(const double& distance) const;

    /**
     * @brief Stel de afmetingen van de window in (als de window wordt resized).
     * @param w De nieuwe breedte van de window in pixels.
     * @param h De nieuwe hoogte van de window in pixels.
     */
    void setDimensions(unsigned int w, unsigned int h);
};
}
#endif //PACKMAN_CAMERA_H
