//
// Created by niels-hertoghs on 12/12/25.
//

#ifndef PACKMAN_VIEWFACTORY_H
#define PACKMAN_VIEWFACTORY_H

#include "BaseFactory.h"
#include "entities/collectableView.h"
#include "entities/ghostView.h"
#include "entities/movableEntityView.h"

#include <memory>

enum class collectableTypes;

namespace view {
class ViewFactory : public BaseFactory {
public:
    virtual std::shared_ptr<packmanView> createPacmanView(std::shared_ptr<logic::movableEntity> pacmanModel) = 0;
    virtual std::shared_ptr<ghostView> createGhostView(std::shared_ptr<logic::Ghost> ghost) = 0;
    virtual std::shared_ptr<wallView> createWallView(std::shared_ptr<logic::wall> _wall) = 0;
    virtual std::shared_ptr<collectableView> createCollectableView(std::shared_ptr<logic::collectable> _collectable) = 0;
};

class ConcreteViewFactory final: public ViewFactory {
    camera& _camera;
    sf::RenderWindow& window;
public:
    ConcreteViewFactory(camera& camera, sf::RenderWindow& window);
    // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
    std::shared_ptr<collectableView> createCollectableView(std::shared_ptr<logic::collectable> _collectable) override;
    std::shared_ptr<packmanView> createPacmanView(std::shared_ptr<logic::movableEntity> pacmanModel) override;
    std::shared_ptr<ghostView> createGhostView(std::shared_ptr<logic::Ghost> ghost) override;
    std::shared_ptr<wallView> createWallView(std::shared_ptr<logic::wall> _wall) override;
};
} // view

#endif //PACKMAN_VIEWFACTORY_H
