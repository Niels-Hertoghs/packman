//
// Created by niels on 11/5/25.
//

#ifndef PACKMAN_WORLD_H
#define PACKMAN_WORLD_H
#include <memory>
#include <vector>
#include <SFML/Graphics/Font.hpp>

#include "camera.h"
#include "render.h"
#include "entities/entity.h"


class world {
private:
    std::vector<std::shared_ptr<wall>> walls;

public:
    world();

    std::unique_ptr<Render> render( const camera& cam,const sf::Font& pacmanFont);
};


#endif //PACKMAN_WORLD_H