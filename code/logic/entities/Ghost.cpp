//
// Created by niels_hertoghs on 11/17/25.
//

#include "Ghost.h"

namespace logic {

    /// ---------------------------------------------------------------------------------------------------------------
    /// @class ghost
    /// ---------------------------------------------------------------------------------------------------------------

    Ghost::Ghost(double x, double y) : movableEntity(x,y,0.95f,directions::UP) {}

    redGhost::redGhost(double x, double y) : Ghost(x,y) {}

    void redGhost::redGhostSubscribe(std::shared_ptr<view::redGhostView> redGhostObserver) {
        this->ghostObserver = redGhostObserver;
    }

    void redGhost::update(double deltaTime, std::vector<std::shared_ptr<wall>>& walls) {
        // random richting uitgaan
    }


} // logic