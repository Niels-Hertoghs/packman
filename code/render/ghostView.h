//
// Created by niels_hertoghs on 11/17/25.
//

#ifndef PACKMAN_GHOSTVIEW_H
#define PACKMAN_GHOSTVIEW_H
#include "movableEntityView.h"

namespace logic {
    class blueGhost;
    class greenGhost;
    class purpleGhost;
    class redGhost;
    class Ghost;
}

namespace view {
    class ghostView : public movableEntityView {
    private:

    public:
        ghostView(sf::RenderWindow& window,camera& cam,const std::vector<std::pair<int,int>>& spriteCo);

        void notify(enum notifications message) override = 0;
    };

    class redGhostView : public ghostView {
    private:
        std::weak_ptr<logic::redGhost> redGhostModel;
    public:
        redGhostView(sf::RenderWindow& window,camera& cam, std::shared_ptr<logic::redGhost>& ghostModel);
        void notify(enum notifications message) override;
    };

    class blueGhostView : public ghostView {
        std::weak_ptr<logic::blueGhost> blueGhostModel;
    public:
        blueGhostView(sf::RenderWindow& window,camera& cam, std::shared_ptr<logic::blueGhost>& ghostModel);
        void notify(enum notifications message) override;
    };

    class greenGhostView : public ghostView {
        std::weak_ptr<logic::greenGhost> greenGhostModel;
    public:
        greenGhostView(sf::RenderWindow& window,camera& cam, std::shared_ptr<logic::greenGhost>& ghostModel);
        void notify(enum notifications message) override;
    };

    class purpleGhostView : public ghostView {
        std::weak_ptr<logic::purpleGhost> purpleGhostModel;
    public:
        purpleGhostView(sf::RenderWindow& window,camera& cam, std::shared_ptr<logic::purpleGhost>& ghostModel);
        void notify(enum notifications message) override;
    };

} // view

#endif //PACKMAN_GHOSTVIEW_H