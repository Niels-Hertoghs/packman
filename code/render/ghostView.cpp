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

    blueGhostView::blueGhostView(sf::RenderWindow& window, camera& cam, std::shared_ptr<logic::blueGhost>& ghostModel)
        : ghostView(window, cam, {{95,300},{95,350}}),blueGhostModel(ghostModel)
    {
        std::pair<unsigned int,unsigned int> pos = cam.worldToPixel(ghostModel->getX(),ghostModel->getY());
        _movable.setPosition(pos.first,pos.second);
    }

    void blueGhostView::notify(enum notifications message) {
        if (message == notifications::CHANGE_POSITION) {
            std::pair<unsigned int,unsigned int> pos;
            if (auto observer = blueGhostModel.lock()) {
                pos = _camera.worldToPixel(observer->getX(),observer->getY());
            }
            _movable.setPosition(pos.first,pos.second);
        } else if ( message == notifications::CHANGE_DIRECTION_DOWN) {
            spriteCo = {{95,100},{95,150}};
        } else if ( message == notifications::CHANGE_DIRECTION_UP) {
            spriteCo = {{95,300},{95,350}};
        } else if ( message == notifications::CHANGE_DIRECTION_RIGHT) {
            spriteCo = {{95,0},{95,50},};
        } else if ( message == notifications::CHANGE_DIRECTION_LEFT) {
            spriteCo = {{95,200},{95,250}};
        }
    }

    greenGhostView::greenGhostView(sf::RenderWindow& window, camera& cam, std::shared_ptr<logic::greenGhost>& ghostModel)
        : ghostView(window, cam, {{195,300},{195,350}}),greenGhostModel(ghostModel)
    {
        std::pair<unsigned int,unsigned int> pos = cam.worldToPixel(ghostModel->getX(),ghostModel->getY());
        _movable.setPosition(pos.first,pos.second);
    }

    void greenGhostView::notify(enum notifications message) {
        if (message == notifications::CHANGE_POSITION) {
            std::pair<unsigned int,unsigned int> pos;
            if (auto observer = greenGhostModel.lock()) {
                pos = _camera.worldToPixel(observer->getX(),observer->getY());
            }
            _movable.setPosition(pos.first,pos.second);
        } else if ( message == notifications::CHANGE_DIRECTION_DOWN) {
            spriteCo = {{195,100},{195,150}};
        } else if ( message == notifications::CHANGE_DIRECTION_UP) {
            spriteCo = {{195,300},{195,350}};
        } else if ( message == notifications::CHANGE_DIRECTION_RIGHT) {
            spriteCo = {{195,0},{195,50},};
        } else if ( message == notifications::CHANGE_DIRECTION_LEFT) {
            spriteCo = {{195,200},{195,250}};
        }
    }

    purpleGhostView::purpleGhostView(sf::RenderWindow& window, camera& cam, std::shared_ptr<logic::purpleGhost>& ghostModel)
        : ghostView(window, cam, {{145,300},{145,350}}),purpleGhostModel(ghostModel)
    {
        std::pair<unsigned int,unsigned int> pos = cam.worldToPixel(ghostModel->getX(),ghostModel->getY());
        _movable.setPosition(pos.first,pos.second);
    }

    void purpleGhostView::notify(enum notifications message) {
        if (message == notifications::CHANGE_POSITION) {
            std::pair<unsigned int,unsigned int> pos;
            if (auto observer = purpleGhostModel.lock()) {
                pos = _camera.worldToPixel(observer->getX(),observer->getY());
            }
            _movable.setPosition(pos.first,pos.second);
        } else if ( message == notifications::CHANGE_DIRECTION_DOWN) {
            spriteCo = {{145,100},{145,150}};
        } else if ( message == notifications::CHANGE_DIRECTION_UP) {
            spriteCo = {{145,300},{145,350}};
        } else if ( message == notifications::CHANGE_DIRECTION_RIGHT) {
            spriteCo = {{145,0},{145,50},};
        } else if ( message == notifications::CHANGE_DIRECTION_LEFT) {
            spriteCo = {{145,200},{145,250}};
        }
    }


} // view