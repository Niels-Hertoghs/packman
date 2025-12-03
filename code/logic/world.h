//
// Created by niels on 11/5/25.
//

#ifndef PACKMAN_WORLD_H
#define PACKMAN_WORLD_H
#include <fstream>
#include <memory>
#include <vector>
#include "../view/notifications.h"
#include "entities/entity.h"
#include "entities/collectable.h"
#include "entities/movableEntity.h"
#include "entities/Ghost.h"
#include "entities/manhattanGhost.h"
#include "Score.h"

namespace logic {
    /**
     * Class world
     * brief bevat alle entities, en bevat de algemene game logica.
     */
    class world {
    private:
        std::vector<std::shared_ptr<wall>> walls;
        std::vector<std::shared_ptr<collectable>> collectables;
        std::vector<std::shared_ptr<invisibleWall>> invisibleWalls;

        std::shared_ptr<redGhost> _redGhost;
        std::shared_ptr<blueGhost> _blueGhost;
        std::shared_ptr<orangeGhost> _orangeGhost;
        std::shared_ptr<greenGhost> _greenGhost;

        std::shared_ptr<Pacman> pacman;
        std::string inputFile;

        std::shared_ptr<Score> score;
    public:
        explicit world(const std::string& inputFile);
        void startWorld(int level);

        void update(float deltaTime);
        void updatePacmanDir(directions) const;

        void subscribeScore(const std::shared_ptr<logic::Score>& score);
        void clear();

        /**
         * Als pacman gestorven is -> alles restart
         */
        void died() const;

        /**
         * @brief Laat alle objecten (die het moeten weten) weten dat Fear mode is gestart.
         */
        void startFearMode() const;

        /**
         * @brief Laat alle objecten (die het moeten weten) weten dat fear mode gedaan is en dat ze terug meten gaan naar chase Mode.
         */
        void startChaseMode() const;


        //getters
        [[nodiscard]] std::vector<std::shared_ptr<wall>> get_walls() const;
        [[nodiscard]] std::vector<std::shared_ptr<collectable>> get_collectables() const;

        [[nodiscard]] std::shared_ptr<redGhost> get_red_ghost() const;
        [[nodiscard]] std::shared_ptr<blueGhost> get_blue_ghost() const;
        [[nodiscard]] std::shared_ptr<orangeGhost> get_orange_ghost() const;
        [[nodiscard]] std::shared_ptr<greenGhost> get_green_ghost() const;

        [[nodiscard]] std::shared_ptr<Pacman> get_pacman() const;
        [[nodiscard]] std::shared_ptr<Score> get_score() const;
    };
}


#endif //PACKMAN_WORLD_H