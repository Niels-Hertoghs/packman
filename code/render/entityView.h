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

namespace logic {
    class wall;
}

class entityView : public Observer {
protected:

public:
    entityView(Stopwatch& stopwatch,sf::RenderWindow& window,camera cam);
    virtual void notify(enum notifications message) = 0;
};

class wallView : public entityView {
protected:
    sf::RectangleShape _wall;
    std::shared_ptr<logic::wall> wallModel;
public:
    wallView(Stopwatch& stopwatch,sf::RenderWindow& window,camera cam,std::shared_ptr<logic::wall> wallM);

    void draw() override;
    void notify(enum notifications message) override;
};

#endif //PACKMAN_ENTITYVIEW_H