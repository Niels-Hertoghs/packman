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
    /**
     * @brief Constructor world.
     * @param inputFile File path naar het text bestand van de map dat afgebeeld moet worden.
     */
    explicit world(const std::string& inputFile);

    /**
     * @brief Waar alle objecten in de game aangemaakt worden en correct geinitializeerd.
     * @param factory Pointer naar de factory.
     */
    void giveFactory(std::unique_ptr<abstractFactory> factory);

    /**
     * @brief Laad de wereld in aan de hand van de Input file.
     * @param level Het level van de ronde.
     */
    void startWorld(int level);

    /**
     * @brief Update alle objecten in de world.
     * @param deltaTime De tijd dat er verstreken is tussen de 2 laatste updates.
     */
    void update(float deltaTime);

    /**
     * @brief Als pacman een andere richting uit moet gaan (wanneer mogelijk).
     * @param dir De volgende richting dat pacman uit moet gaan zodra het mogelijk is.
     */
    void updatePacmanDir(directions dir) const;

    /**
     * @brief Laat de score "subscriben" aan de world.
     * @param score Pointer naar de score observer.
     */
    void subscribeScore(std::shared_ptr<Score> score);

    /**
     * @brief Notified alle observers in world met de notification.
     * @param notification de notificatie die gecommuniceerd moet worden met de observers.
     */
    void notifyObservers(const scoreNotifications& notification) const;

    /**
     * @brief Reset alles in de world.
     */
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
    /**
     * @return Pointer naar de score observer.
     */
    [[nodiscard]] std::shared_ptr<Score> get_score() const;

    /**
     * @brief Default destructor.
     */
    ~world() = default;
};
}


#endif //PACKMAN_WORLD_H
