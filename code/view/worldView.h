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

namespace view {
/**
 * @class worldView
 * @brief De wereld observer, die alle entity observers bevat en aanstuurt.
 */
class worldView final {
private:
    std::vector<std::shared_ptr<wallView>> walls;               /// Alle wall observers in de wereld.
    std::vector<std::shared_ptr<collectableView>> collectables; /// Alle collectable observers in de wereld.
    std::shared_ptr<packmanView> pacman;                        /// De pacman observer.
    std::vector<std::shared_ptr<ghostView>> ghosts;             ///  Vector met alle ghost observers.

    std::shared_ptr<ScoreView> score; /// De score observer.
public:
    /**
     * @brief Constructor
     * @param camera Camera klasse voor het omzetten naar pixel coordinaten.
     * @param window Waar het op moet worden afgebeeld.
     * @param score Pointer naar de score logica.
     * @param manager De state manager voor de score view.
     */
    worldView(camera& camera, sf::RenderWindow& window, const std::shared_ptr<logic::Score>& score,
              std::shared_ptr<stateManeger> manager);


    /**
     * @brief Laat alle observers tekenen in de window, indien nodig.
     */
    void draw() const;

    /**
     * @brief cleart alle private members. reset het dus.
     */
    void clear();

    /**
     * @brief Voegt een collectable observer toe aan de world view.
     * @param collectableV De collectable observer.
     */
    void addCollectableView(const std::shared_ptr<collectableView>& collectableV);

    /**
     * @brief Voegt een ghost observer toe aan de world view.
     * @param ghostV De ghost observer.
     */
    void addGhostView(const std::shared_ptr<ghostView>& ghostV);

    /**
    * @brief Voegt een wall observer toe aan de world view.
    * @param wallV De wall observer.
    */
    void addWallView(const std::shared_ptr<wallView>& wallV);

    /**
     * @brief Voegt de pacman observer toe aan de world view.
     * @param pacmanV De pacman observer.
     */
    void addPacmanView(const std::shared_ptr<packmanView>& pacmanV);

    /**
     * @brief Default destructor.
     */
    ~worldView() = default;
};
}

#endif //PACKMAN_WORLDVIEW_H
