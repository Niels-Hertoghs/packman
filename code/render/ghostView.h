//
// Created by niels_hertoghs on 11/17/25.
//

#ifndef PACKMAN_GHOSTVIEW_H
#define PACKMAN_GHOSTVIEW_H
#include "movableEntityView.h"

namespace logic {
    class redGhost;
    class Ghost;
}

namespace view {
    class ghostView : public movableEntityView {
    private:

    public:
        ghostView(Stopwatch& stopwatch,sf::RenderWindow& window,camera& cam,const std::vector<std::pair<int,int>>& spriteCo);

        void notify(enum notifications message) override = 0;
    };

    class redGhostView : public ghostView {
    private:
        std::weak_ptr<logic::redGhost> redGhostModel;
    public:
        redGhostView(Stopwatch& stopwatch,sf::RenderWindow& window,camera& cam, std::shared_ptr<logic::redGhost>& ghostModel);
        void notify(enum notifications message) override;
    };
} // view

#endif //PACKMAN_GHOSTVIEW_H