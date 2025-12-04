//
// Created by niels_hertoghs on 11/10/25.
//

#ifndef PACKMAN_OBSERVER_H
#define PACKMAN_OBSERVER_H
#include <SFML/Graphics.hpp>
#include "view/camera.h"
#include "view/notifications.h"

/**
 * @class IObserver
 * @brief Basis klasse voor alle observers.
 */
class IObserver {
public:
    /**
     * @brief Default destructor.
     */
    virtual ~IObserver() = default;
};

namespace view {
    /**
     * @class Observer
     * @brief Abstracte klasse voor alle view observers.
     */
    class Observer : public IObserver {
    protected:
        sf::RenderWindow& window; /// Reference naar de window waar het op getekend moet worden.
        camera& _camera; /// Reference naar de camera klasse voor het omzetten van wereld coordinaten naar pixel coordinaten.

    public:
        /**
         * @brief Constructor
         * @param window Waar het op moet worden afgebeeld.
         * @param camera Camera klasse voor het omzetten naar pixel coordinaten.
         */
        Observer(sf::RenderWindow& window,camera& camera);

        // pure virtual methodes
        /**
         * @brief Methode die wordt aangeroepen als de observer een notificatie ontvangt.
         * @param message De message die de observer ontvangt.
         */
        virtual void notify(enum notifications message) = 0;

        /**
         * @brief Methode om de observer te tekenen op de window.
         */
        virtual void draw() = 0;
    };
}


#endif //PACKMAN_OBSERVER_H