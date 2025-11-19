//
// Created by niels_hertoghs on 11/17/25.
//

#include "ghostView.h"
#include "../logic/entities/Ghost.h"

namespace view {
    ghostView::ghostView(sf::RenderWindow& window, camera& cam,const std::vector<std::pair<int,int>>& spriteCo)
    : movableEntityView(window, cam,spriteCo,2) {}

    redGhostView::redGhostView(sf::RenderWindow& window, camera& cam, std::shared_ptr<logic::redGhost>& ghostModel)
        : ghostView(window, cam, {{-5,300},{-5,350}}),redGhostModel(ghostModel)
    {
        std::pair<unsigned int,unsigned int> pos = cam.worldToPixel(ghostModel->getX(),ghostModel->getY());
        _movable.setPosition(pos.first,pos.second);
    }

    void redGhostView::notify(enum notifications message) {
        if (message == notifications::CHANGE_POSITION) {
            std::pair<unsigned int,unsigned int> pos;
            if (auto observer = redGhostModel.lock()) {
                pos = _camera.worldToPixel(observer->getX(),observer->getY());
            }
            _movable.setPosition(pos.first,pos.second);
        } else if ( message == notifications::CHANGE_DIRECTION_DOWN) {
            spriteCo = {{-5,100},{-5,150}};
        } else if ( message == notifications::CHANGE_DIRECTION_UP) {
            spriteCo = {{-5,300},{-5,350}};
        } else if ( message == notifications::CHANGE_DIRECTION_RIGHT) {
            spriteCo = {{-5,0},{-5,50},};
        } else if ( message == notifications::CHANGE_DIRECTION_LEFT) {
            spriteCo = {{-5,200},{-5,250}};
        }
    }


} // view