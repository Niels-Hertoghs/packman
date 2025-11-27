//
// Created by niels_hertoghs on 11/17/25.
//

#ifndef PACKMAN_GHOSTVIEW_H
#define PACKMAN_GHOSTVIEW_H
#include "movableEntityView.h"

namespace logic {
    class blueGhost;
    class greenGhost;
    class orangeGhost;
    class redGhost;
    class Ghost;
}

namespace view {
    class ghostView : public movableEntityView {
    private:

    public:
        ghostView(sf::RenderWindow &window, camera &cam, std::shared_ptr<logic::movableEntity>& ghostModel,
                  const std::vector<std::pair<int, int> > &spriteCo,
                  const std::vector<std::vector<std::pair<int, int> > > &allSprites);
    };

    class redGhostView : public ghostView {
    private:
    public:
        redGhostView(sf::RenderWindow& window,camera& cam, std::shared_ptr<logic::movableEntity> ghostModel);
    };

    class blueGhostView : public ghostView {
    public:
        blueGhostView(sf::RenderWindow& window,camera& cam, std::shared_ptr<logic::movableEntity> ghostModel);
    };

    class greenGhostView : public ghostView {
    public:
        greenGhostView(sf::RenderWindow& window,camera& cam, std::shared_ptr<logic::movableEntity> ghostModel);
    };

    class orangeGhostView : public ghostView {
    public:
        orangeGhostView(sf::RenderWindow& window,camera& cam, std::shared_ptr<logic::movableEntity> ghostModel);
    };

} // view

#endif //PACKMAN_GHOSTVIEW_H