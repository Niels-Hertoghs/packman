//
// Created by niels_hertoghs on 11/17/25.
//

#ifndef PACKMAN_GHOSTVIEW_H
#define PACKMAN_GHOSTVIEW_H
#include "movableEntityView.h"

// Forward declarations
namespace logic {
    class blueGhost;
    class greenGhost;
    class orangeGhost;
    class redGhost;
    class Ghost;
}

namespace view {
    /**
 * @class ghostView
 * @brief Abstracte klasse voor alle ghost observers.
 */
    class ghostView : public movableEntityView {
    public:
        /**
     * @brief Constructor
     * @param window Waar het op moet worden afgebeeld.
     * @param cam Camera klasse voor het omzetten naar pixel coordinaten.
    * @param x De x coo van de start locatie van de movable. (relatief tussen -1, en 1)
    * @param y De y coo van de start locatie van de movable. (relatief tussen -1, en 1)
     * @param spriteCo De coordinaten van de sprites voor deze ghost in de gegeven richting.
     * @param allSprites Alle coordinaten van de sprites voor deze ghost in alle richtingen (volgorde: down, up, right, left).
     */
        ghostView(sf::RenderWindow &window, camera &cam, double x, double y,
                  const std::vector<std::pair<int, int> > &spriteCo,
                  const std::vector<std::vector<std::pair<int, int> > > &allSprites);

        // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
        bool isGhost() override;

        /**
    * @brief Default destructor.
    */
        ~ghostView() override = default;
    };

    /**
 * @class redGhostView
 * @brief Concrete klasse voor de redGhost.
 */
    class redGhostView final : public ghostView {
    public:
        /**
     * @brief Constructor
     * @param window Waar het op moet worden afgebeeld.
     * @param cam Camera klasse voor het omzetten naar pixel coordinaten.
    * @param x De x coo van de start locatie van de movable. (relatief tussen -1, en 1)
    * @param y De y coo van de start locatie van de movable. (relatief tussen -1, en 1)
     */
        redGhostView(sf::RenderWindow &window, camera &cam, double x, double y);

        /**
     * @brief Default destructor.
     */
        ~redGhostView() override = default;
    };

    /**
 * @class blueGhostView
 * @brief Concrete klasse voor de blueGhost.
 */
    class blueGhostView final : public ghostView {
    public:
        /**
    * @brief Constructor
    * @param window Waar het op moet worden afgebeeld.
    * @param cam Camera klasse voor het omzetten naar pixel coordinaten.
    * @param x De x coo van de start locatie van de movable. (relatief tussen -1, en 1)
    * @param y De y coo van de start locatie van de movable. (relatief tussen -1, en 1)
    */
        blueGhostView(sf::RenderWindow &window, camera &cam, double x, double y);

        /**
     * @brief Default destructor.
     */
        ~blueGhostView() override = default;
    };

    /**
* @class greenGhostView
* @brief Concrete klasse voor de greenGhost.
*/
    class greenGhostView final : public ghostView {
    public:
        /**
    * @brief Constructor
    * @param window Waar het op moet worden afgebeeld.
    * @param cam Camera klasse voor het omzetten naar pixel coordinaten.
    * @param x De x coo van de start locatie van de movable. (relatief tussen -1, en 1)
    * @param y De y coo van de start locatie van de movable. (relatief tussen -1, en 1)
    */
        greenGhostView(sf::RenderWindow &window, camera &cam, double x, double y);

        /**
    * @brief Default destructor.
    */
        ~greenGhostView() override = default;
    };

    /**
* @class orangeGhostView
* @brief Concrete klasse voor de orangeGhost.
*/
    class orangeGhostView final : public ghostView {
    public:
        /**
    * @brief Constructor
    * @param window Waar het op moet worden afgebeeld.
    * @param cam Camera klasse voor het omzetten naar pixel coordinaten.
    * @param x De x coo van de start locatie van de movable. (relatief tussen -1, en 1)
    * @param y De y coo van de start locatie van de movable. (relatief tussen -1, en 1)
    */
        orangeGhostView(sf::RenderWindow &window, camera &cam, double x, double y);

        /**
     * @brief Default destructor.
     */
        ~orangeGhostView() override = default;
    };
} // view

#endif //PACKMAN_GHOSTVIEW_H