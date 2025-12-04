//
// Created by niels_hertoghs on 11/13/25.
//

#ifndef PACKMAN_WORLDVIEW_H
#define PACKMAN_WORLDVIEW_H
#include <memory>
#include "../observer.h"
#include "entities/entityView.h"
#include "entities/movableEntityView.h"
#include "entities/collectableView.h"
#include "entities/ghostView.h"
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
    class worldView final : public IObserver {
    private:
        std::vector<std::shared_ptr<wallView>> walls; /// Alle wall observers in de wereld.
        std::vector<std::shared_ptr<fruitView>> fruits; /// Alle fruit observers in de wereld.
        std::vector<std::shared_ptr<coinView>> coins; /// Alle coin observers in de wereld.
        std::shared_ptr<view::packmanView> pacman; /// De pacman observer.

        std::shared_ptr<view::redGhostView> redGhost; /// De red ghost observer.
        std::shared_ptr<view::blueGhostView> blueGhost; /// De blue ghost observer.
        std::shared_ptr<view::greenGhostView> greenGhost; /// De green ghost observer.
        std::shared_ptr<view::orangeGhostView> orangeGhost; /// De orange ghost observer.

        std::shared_ptr<view::ScoreView> score; /// De score observer.
    public:
        /**
         * @brief Constructor
         * @param _wereld Pointer naar de logica van de wereld.
         * @param camera Camera klasse voor het omzetten naar pixel coordinaten.
         * @param window Waar het op moet worden afgebeeld.
         * @param score Pointer naar de score logica.
         */
        worldView(const std::shared_ptr<logic::world>& _wereld,camera& camera, sf::RenderWindow& window,std::shared_ptr<logic::Score>& score);

        /**
         * @brief Laat alle observers tekenen in de window, indien nodig.
         */
        void draw();
    };
}

#endif //PACKMAN_WORLDVIEW_H