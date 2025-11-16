//
// Created by niels on 11/5/25.
//

#ifndef PACKMAN_WORLD_H
#define PACKMAN_WORLD_H
#include <fstream>
#include <memory>
#include <vector>
#include <SFML/Graphics/Font.hpp>
#include "render/notifications.h"
#include "camera.h"
#include "observer.h"
#include "render/render.h"
#include "logic/entities/entity.h"
#include "logic/entities/collectable.h"
#include "logic/entities/movableEntity.h"

namespace logic {
    /**
     * Class world
     * brief bevat alle entities, en bevat de algemene game logica.
     */
    class world {
    private:
        std::vector<std::shared_ptr<wall>> walls;
        std::vector<std::shared_ptr<fruit>> fruits;
        std::vector<std::shared_ptr<coin>> coins;
        std::shared_ptr<Packman> pacman;
        std::string inputFile;

        std::shared_ptr<Score> score;
    public:
        explicit world(const std::string& inputFile);
        void startWorld();

        std::shared_ptr<render::Render> render( const camera& cam,const sf::Font& pacmanFont);
        void update(float deltaTime);
        void updatePacmanDir(directions);

        void subscribeScore(std::shared_ptr<Score> score);

        //getters
        [[nodiscard]] std::vector<std::shared_ptr<wall>> get_walls() const;
        [[nodiscard]] std::vector<std::shared_ptr<fruit>> get_fruits() const;
        [[nodiscard]] std::vector<std::shared_ptr<coin>> get_coins() const;

        [[nodiscard]] std::shared_ptr<Packman> get_pacman() const;
    };
}


#endif //PACKMAN_WORLD_H