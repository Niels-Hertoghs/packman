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
#include "entities/collectable.h"
#include  "entities/movableEntity.h"

class world {
private:
    std::vector<std::shared_ptr<wall>> walls;
    std::vector<std::shared_ptr<collectable>> collectables;
    std::shared_ptr<Packman> pacman;
public:
    world(const std::string& inputFile);


    Render* render( const camera& cam,const sf::Font& pacmanFont);
    void update(float deltaTime);
    void updatePacmanDir(const std::string& direction);
};


#endif //PACKMAN_WORLD_H