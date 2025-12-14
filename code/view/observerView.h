//
// Created by niels_hertoghs on 12/14/25.
//

#ifndef PACKMAN_OBSERVERVIEW_H
#define PACKMAN_OBSERVERVIEW_H

#include <SFML/Graphics.hpp>
#include "camera.h"
#include "../logic/notifications.h"
#include "../logic/Observer.h"
#include "observerView.h"

namespace view {
/**
 * @class ObserverView
 * @brief Abstracte klasse voor alle view observers.
 */
    class ObserverView : public logic::Observer<notifications> {
protected:
    sf::RenderWindow& window; /// Reference naar de window waar het op getekend moet worden.
    camera& _camera; /// Reference naar de camera klasse voor het omzetten van wereld coordinaten naar pixel coordinaten.

public:
    /**
     * @brief Constructor
     * @param window Waar het op moet worden afgebeeld.
     * @param camera Camera klasse voor het omzetten naar pixel coordinaten.
     */
    ObserverView(sf::RenderWindow& window,camera& camera);

    void notify(const notifications& message) override = 0;

    /**
     * @brief Methode om de observer te tekenen op de window.
     */
    virtual void draw() = 0;
};
}

#endif //PACKMAN_OBSERVERVIEW_H