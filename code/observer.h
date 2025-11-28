//
// Created by niels_hertoghs on 11/10/25.
//

#ifndef PACKMAN_OBSERVER_H
#define PACKMAN_OBSERVER_H
#include <SFML/Graphics.hpp>

#include "view/camera.h"
#include "logic/Stopwatch.h"
#include "view/notifications.h"
class IObserver {
public:
    virtual ~IObserver() = default;
};

namespace view {
    class Observer : public IObserver {
    protected:
        sf::RenderWindow& window;
        camera& _camera;

    public:
        Observer(sf::RenderWindow& window,camera& camera);

        virtual void notify(enum notifications message) = 0;
        virtual void draw() = 0;
    };
}


#endif //PACKMAN_OBSERVER_H