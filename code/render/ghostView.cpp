//
// Created by niels_hertoghs on 11/17/25.
//

#include "ghostView.h"
#include "../logic/entities/Ghost.h"

namespace view {
    ghostView::ghostView(Stopwatch& stopwatch, sf::RenderWindow& window, camera& cam,const std::vector<std::pair<int,int>>& spriteCo)
    : movableEntityView(stopwatch, window, cam,spriteCo,2) {}

    redGhostView::redGhostView(Stopwatch& stopwatch, sf::RenderWindow& window, camera& cam, std::shared_ptr<logic::redGhost>& ghostModel)
        : ghostView(stopwatch, window, cam, {{-5,300},{-5,350},{847,51},{847,1}}),redGhostModel(ghostModel)
    {
        std::pair<unsigned int,unsigned int> pos = cam.worldToPixel(ghostModel->getX(),ghostModel->getY());
        _movable.setPosition(pos.first,pos.second);
    }

    void redGhostView::notify(enum notifications message) {
        //yapya
    }


} // view