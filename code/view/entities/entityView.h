//
// Created by niels_hertoghs on 11/13/25.
//

#ifndef PACKMAN_ENTITYVIEW_H
#define PACKMAN_ENTITYVIEW_H
#include <SFML/Graphics.hpp>

#include "../../observer.h"
#include "../notifications.h"
#include "../camera.h"
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
    class entityView : public Observer {
    public:
        /**
         * @brief Constructor
         * @param window Waar het op moet worden afgebeeld.
         * @param cam Camera klasse voor het omzetten naar pixel coordinaten.
         */
        entityView(sf::RenderWindow& window,camera& cam);

        // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
        void notify(enum notifications message) override = 0;
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
        std::weak_ptr<logic::wall> wallModel;  /// Pointer naar de logica van de muur.
    public:
        /**
        * @brief Constructor
        * @param window Waar het op moet worden afgebeeld.
        * @param cam Camera klasse voor het omzetten naar pixel coordinaten.
        * @param wallM Pointer naar de logica van de muur.
        */
        wallView(sf::RenderWindow& window,camera& cam,std::shared_ptr<logic::wall>& wallM);

        // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
        void draw() override;
        void notify(enum notifications message) override;

        /**
         * @brief Default destructor.
         */
        ~wallView() override = default;
    };
}
#endif //PACKMAN_ENTITYVIEW_H