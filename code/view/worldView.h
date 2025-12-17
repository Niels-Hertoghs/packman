//
// Created by niels_hertoghs on 11/13/25.
//

#ifndef PACKMAN_WORLDVIEW_H
#define PACKMAN_WORLDVIEW_H
#include <memory>
#include "entities/entityView.h"
#include "entities/movableEntityView.h"
#include "entities/collectableView.h"
#include "entities/ghostView.h"
#include "../logic/Score.h"
#include "ScoreView.h"


// Forward declarations
namespace logic {
class world;
}


namespace view {
/**
 * @class worldView
 * @brief De wereld observer, die alle entity observers bevat en aanstuurt.
 */
class worldView final {
private:
    std::vector<std::shared_ptr<wallView> > walls;               /// Alle wall observers in de wereld.
    std::vector<std::shared_ptr<collectableView> > collectables; /// Alle collectable observers in de wereld.
    std::shared_ptr<view::packmanView> pacman;                   /// De pacman observer.

    std::vector<std::shared_ptr<ghostView> > ghosts;

    std::shared_ptr<ScoreView> score; /// De score observer.
public:
    /**
     * @brief Constructor
     * @param _wereld Pointer naar de logica van de wereld.
     * @param camera Camera klasse voor het omzetten naar pixel coordinaten.
     * @param window Waar het op moet worden afgebeeld.
     * @param score Pointer naar de score logica.
     */
    worldView(camera& camera, sf::RenderWindow& window,const std::shared_ptr<logic::Score>& score,std::shared_ptr<stateManeger> manager);


    /**
     * @brief Laat alle observers tekenen in de window, indien nodig.
     */
    void draw() const;

    void clear();

    void addCollectableView(const std::shared_ptr<collectableView>& collectableV);
    void addGhostView(const std::shared_ptr<ghostView>& ghostV);
    void addWallView(const std::shared_ptr<wallView>& wallV);
    void addPacmanView(const std::shared_ptr<packmanView>& pacmanV);


    ~worldView() = default;
};
}

#endif //PACKMAN_WORLDVIEW_H
