//
// Created by niels_hertoghs on 11/13/25.
//

#ifndef PACKMAN_ENTITYVIEW_H
#define PACKMAN_ENTITYVIEW_H
#include <SFML/Graphics.hpp>

#include "../observerView.h"
#include "../../logic/notifications.h"
#include "../camera.h"
#include "../../logic/Observer.h"
#include "../../logic/entities/entity.h"

// Forward declarations
namespace logic {
    class wall;
}

namespace view {
    /**
 * @class entityView
 * @brief Abstracte klasse voor alle entity observers.
 */
    class entityView : public ObserverView<logic::notifications> {
    protected:
        double x, y; /// de positie van van de entity
    public:
        /**
     * @brief Constructor
     * @param window Waar het op moet worden afgebeeld.
     * @param cam Camera klasse voor het omzetten naar pixel coordinaten.
     */
        entityView(sf::RenderWindow &window, camera &cam, double x, double y);

        // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
        void notify(const logic::notifications &message) override = 0;

        void draw() override = 0;

        /**
     * @brief Default destructor.
     */
        ~entityView() override = default;
    };

    /**
* @class wallView
* @brief Concrete klasse voor alle wall observers.
*/
    class wallView final : public entityView {
    protected:
        sf::RectangleShape _wall; /// Representatie van de muur.
    public:
        /**
    * @brief Constructor
    * @param window Waar het op moet worden afgebeeld.
    * @param cam Camera klasse voor het omzetten naar pixel coordinaten.
    * @param wallM Pointer naar de logica van de muur.
    */
        wallView(sf::RenderWindow &window, camera &cam, double x, double y);

        // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
        void draw() override;

        void notify(const logic::notifications &message) override;

        /**
     * @brief Default destructor.
     */
        ~wallView() override = default;
    };
}
#endif //PACKMAN_ENTITYVIEW_H