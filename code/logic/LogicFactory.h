//
// Created by niels-hertoghs on 12/12/25.
//

#ifndef PACKMAN_LOGICFACTORY_H
#define PACKMAN_LOGICFACTORY_H

#include "entities/movableEntity.h"
#include "entities/collectable.h"
#include "entities/Ghost.h"
#include "entities/manhattanGhost.h"

#include <memory>

/**
 * @brief Alle mogelijke types van collectables.
 */
enum class collectableTypes {
    COIN,
    FRUIT
};


namespace logic {
/**
 * @class LogicFactory
 * @brief Abstracte basis klasse voor alle logic factories.
 */
class LogicFactory {
public:
    virtual ~LogicFactory() = default;

private:
    /**
     * @brief Maakt een nieuwe Pacman aan.
     * @return Shared pointer naar een nieuw gemaakte Pacman.
     */
    virtual std::shared_ptr<Pacman> createPacman(double x, double y, float speed) = 0;

    /**
     * @brief Maakt een nieuwe ghost aan.
     * @param typeGhost Wat voor type Ghost er gemaakt moet worden.
     * @return Pointer naar de gemaakte ghost.
     */
    virtual std::shared_ptr<Ghost> createGhost(ghostTypes typeGhost, double x, double y, float speed, int points) = 0;

    /**
     * @brief Maakt een nieuwe wall aan.
     * @return Pointer naar de gemaakte wall.
     */
    virtual std::shared_ptr<wall> createWall(double x, double y) = 0;

    virtual std::shared_ptr<invisibleWall> createInvisibleWall(double x, double y) = 0;

    /**
     * @brief Maakt een nieuwe collectable aan.
     * @param typeCollectable Wat voor type collectable er gemaakt moet worden.
     * @return Pointer naar de gemaakte collectable.
     */
    virtual std::shared_ptr<collectable> createCollectable(collectableTypes typeCollectable, double x, double y,
                                                           int points) = 0;
};

/**
 * @class ConcreteLogicFactory
 * @brief Concrete klasse voor de logic factory.
 */
class ConcreteLogicFactory final : public LogicFactory {
public:
    // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
    std::shared_ptr<Pacman> createPacman(double x, double y, float speed) override;

    std::shared_ptr<Ghost> createGhost(ghostTypes typeGhost, double x, double y, float speed, int points) override;

    std::shared_ptr<wall> createWall(double x, double y) override;

    std::shared_ptr<invisibleWall> createInvisibleWall(double x, double y) override;

    std::shared_ptr<collectable>
    createCollectable(collectableTypes typeCollectable, double x, double y, int points) override;
};
} // logic

#endif //PACKMAN_LOGICFACTORY_H
