//
// Created by niels on 11/5/25.
//

#ifndef PACKMAN_WORLD_H
#define PACKMAN_WORLD_H
#include <memory>
#include <vector>
#include "notifications.h"
#include "entities/entity.h"
#include "entities/collectable.h"
#include "entities/movableEntity.h"
#include "entities/Ghost.h"
#include "Score.h"
#include "abstractFactory.h"

namespace logic {
/**
 * @Class world
 * @brief Bevat alle entities, en bevat de algemene game logica.
 */
class world {
    std::vector<std::shared_ptr<wall>> walls; /// De walls in de world.
    std::vector<std::shared_ptr<invisibleWall>> invisibleWalls;
    /// De invisible walls in de world (worden niet weergegeven, movables kunnen er niet door).
    ///
    std::vector<std::shared_ptr<collectable>> collectables; /// de collectables in de world.
    std::vector<std::shared_ptr<Ghost>> ghosts; /// de ghosts in de world.
    std::shared_ptr<Pacman> pacman; /// pointer naar pacman.
    std::string inputFile; /// File path naar het text bestand van de map dat afgebeeld moet worden.
    std::shared_ptr<Score> score; /// Pointer naar de score observer.
    std::unique_ptr<abstractFactory> factory; /// Pointer naar de factory.
public:
    explicit world(const std::string& inputFile);

    void giveFactory(std::unique_ptr<abstractFactory> factory);

    void startWorld(int level);

    void update(float deltaTime);

    void updatePacmanDir(directions) const;

    void subscribeScore(std::shared_ptr<Score> score);

    void notifyObservers(const scoreNotifications& notification) const;

    void clear();

    /**
     * Als pacman gestorven is -> alles restart
     */
    void died() const;

    /**
     * @brief Laat alle objecten (die het moeten weten) weten dat Fear mode is gestart.
     */
    void startFearMode() const;


    //getters
    [[nodiscard]] std::vector<std::shared_ptr<wall>> get_walls() const;

    [[nodiscard]] std::vector<std::shared_ptr<collectable>> get_collectables() const;

    [[nodiscard]] std::vector<std::shared_ptr<Ghost>> get_ghosts() const;

    [[nodiscard]] std::shared_ptr<Pacman> get_pacman() const;

    [[nodiscard]] std::shared_ptr<Score> get_score() const;
};
}


#endif //PACKMAN_WORLD_H
