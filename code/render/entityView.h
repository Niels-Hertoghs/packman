//
// Created by niels_hertoghs on 11/13/25.
//

#ifndef PACKMAN_ENTITYVIEW_H
#define PACKMAN_ENTITYVIEW_H
#include <SFML/Graphics.hpp>

#include "../observer.h"
#include "notifications.h"
#include "../camera.h"
#include "../logic/entities/entity.h"

class entityView : public Observer {
protected:
    camera _camera;
public:
    entityView(Stopwatch& stopwatch,sf::RenderWindow& window,camera cam);
    virtual void notify(enum notifications message) = 0;
};

class wallView : public entityView {
protected:
    sf::RectangleShape _wall;
    logic::wall wallModel;
public:
    wallView(Stopwatch& stopwatch,sf::RenderWindow& window,camera cam,logic::wall& wallM);

    void draw() override;
};

#endif //PACKMAN_ENTITYVIEW_H