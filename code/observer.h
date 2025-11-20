//
// Created by niels_hertoghs on 11/10/25.
//

#ifndef PACKMAN_OBSERVER_H
#define PACKMAN_OBSERVER_H
#include <SFML/Graphics.hpp>

#include "camera.h"
#include "Stopwatch.h"
#include "render/notifications.h"
class IObserver {
public:
    virtual ~IObserver() = default;
};

class Observer : public IObserver {
protected:
    sf::RenderWindow& window;
    camera& _camera;

public:
    Observer(sf::RenderWindow& window,camera& camera);

    virtual void notify(enum notifications message) = 0;
    virtual void draw() = 0;
};


#endif //PACKMAN_OBSERVER_H