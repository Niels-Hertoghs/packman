//
// Created by niels-hertoghs on 12/12/25.
//

#ifndef PACKMAN_VIEWFACTORY_H
#define PACKMAN_VIEWFACTORY_H

#include "abstractFactory.h"
#include "worldView.h"
#include <memory>

namespace view {
/**
 * @class concreteFactory
 * @brief Maakt alle logic een view objecten aan en linkt ze aan elkaar.
 */
class concreteFactory final : public logic::abstractFactory {
    camera& _camera;                   /// De camera klasse voor het omzetten van relatieve coo naar pixel coo.
    sf::RenderWindow& window;          /// De window waar de view in afgebeeld moet worden.
    std::shared_ptr<worldView> worldV; /// De world view klasse waar alle observers in beheerd worden.
public:
    /**
     * @brief COnstructor
     * @param camera De camera klasse.
     * @param window De view window.
     * @param wereld De beheerder van alle observer objecten.
     */
    concreteFactory(camera& camera, sf::RenderWindow& window, std::shared_ptr<worldView> wereld);

    // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
    std::shared_ptr<logic::Pacman> createPacman(double x, double y, float speed) override;

    std::shared_ptr<logic::Ghost>
    createGhost(logic::ghostTypes typeGhost, double x, double y, float speed, int points) override;

    std::shared_ptr<logic::wall> createWall(double x, double y) override;

    std::shared_ptr<logic::invisibleWall> createInvisibleWall(double x, double y) override;

    std::shared_ptr<logic::collectable> createCollectable(logic::collectableTypes typeCollectable, double x, double y,
                                                          int points) override;
};
} // view

#endif //PACKMAN_VIEWFACTORY_H
