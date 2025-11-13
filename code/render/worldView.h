//
// Created by niels_hertoghs on 11/13/25.
//

#ifndef PACKMAN_WORLDVIEW_H
#define PACKMAN_WORLDVIEW_H
#include <memory>

#include "../observer.h"
#include "entityView.h"
#include "../world.h"

// dit is voor als er objecten worden verwijderd dan doet die hier iets, bij de notify
// anderws geeft die de melding door denk ik
class worldView : public IObserver {
private:
    std::vector<std::shared_ptr<wallView>> walls;
    // std::vector<std::shared_ptr<collectableView>> collectables;
    // std::shared_ptr<PackmanView> pacman;
public:
    worldView(logic::world& wereld);
    void draw();
};


#endif //PACKMAN_WORLDVIEW_H