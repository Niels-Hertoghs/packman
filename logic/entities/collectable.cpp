//
// Created by niels on 11/6/25.
//

#include "collectable.h"

#include "../render.h"

collectable::collectable(float x, float y) : entity(x,y ){}

coin::coin(float x, float y) : collectable(x,y){}

void coin::render(Render *render) {
    render->addCoin(this->getX(),this->getY());
}


