//
// Created by niels-hertoghs on 12/12/25.
//

#ifndef PACKMAN_LOGICFACTORY_H
#define PACKMAN_LOGICFACTORY_H

#include "entities/movableEntity.h"
#include "entities/collectable.h"
#include "entities/Ghost.h"
#include <memory>

namespace logic {
/**
* @class abstractFactory
* @brief Abstracte basis klasse voor alle logic factories.
*/
class abstractFactory {
public:
    /**
     * @brief Default constructor.
     */
    abstractFactory() = default;

    /**
     * @brief Maakt een nieuwe Pacman aan.
     * @param x De x positie van pacman.
     * @param y De x positie van pacman.
     * @param speed De snelheid van pacman.
     * @return Shared pointer naar een nieuw gemaakte Pacman.
     */
    virtual std::shared_ptr<Pacman> createPacman(double x, double y, float speed) = 0;

    /**
     * @brief Maakt een nieuwe ghost aan.
     * @param typeGhost Wat voor type Ghost er gemaakt moet worden (red,blue,orange,green).
     * @param x De x positie van ghost.
     * @param y De x positie van ghost.
     * @param speed De snelheid van ghost.
     * @param points Aantal points dat een ghost waard is.
     * @return Pointer naar de gemaakte ghost.
     */
    virtual std::shared_ptr<Ghost> createGhost(ghostTypes typeGhost, double x, double y, float speed, int points) =
    0;

    /**
     * @brief Maakt een nieuwe wall aan.
     * @param x De x positie van wall.
     * @param y De x positie van wall.
     * @return Pointer naar de gemaakte wall.
     */
    virtual std::shared_ptr<wall> createWall(double x, double y) = 0;

    /**
     * @brief Maakt een nieuwe wall aan.
     * @param x De x positie van wall.
     * @param y De x positie van wall.
     * @return Pointer naar de gemaakte wall.
     */
    virtual std::shared_ptr<invisibleWall> createInvisibleWall(double x, double y) = 0;

    /**
     * @brief Maakt een nieuwe collectable aan.
     * @param typeCollectable Wat voor type collectable er gemaakt moet worden.
     * @param x De x positie van collectable.
     * @param y De x positie van collectable.
     * @param points De snelheid van collectable.
     * @return Pointer naar de gemaakte collectable.
     */
    virtual std::shared_ptr<collectable> createCollectable(collectableTypes typeCollectable, double x, double y,
                                                           int points) = 0;

    /**
     * @brief Default destructor.
     */
    virtual ~abstractFactory() = default;
};
} // logic

#endif //PACKMAN_LOGICFACTORY_H
