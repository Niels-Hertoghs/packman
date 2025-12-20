//
// Created by niels_hertoghs on 11/20/25.
//

#ifndef PACKMAN_SCOREVIEW_H
#define PACKMAN_SCOREVIEW_H
#include "observerView.h"
#include <memory>

namespace logic {
class scoreViewNotifications;
}

namespace view {
class stateManeger;
/**
* @class ScoreView
* @brief Concrete klasse voor de score observer.
*/
class ScoreView final : public ObserverView<logic::scoreViewNotifications> {
    sf::Font font;      /// Font voor de score tekst.
    sf::Text scoreText; /// Tekst voor de score.
    sf::Text levelText; /// Tekst voor het level.
    sf::Text livesText; /// Tekst voor het aantal levens.

    std::shared_ptr<stateManeger> _manager;
    /// Pointer naar de state manager, om states te kunnen veranderen indien nodig.
public:
    /**
     * @brief Constructor
     * @param window Waar het op moet worden afgebeeld.
     * @param cam Camera klasse voor het omzetten naar pixel coordinaten.
     * @param score De initiele score.
     * @param level Het initiele level.
     * @param lives Het initiele aantal lives.
     * @param manager Pointer naar de state manager voor het toevoegen van bepaalde states.
     */
    ScoreView(sf::RenderWindow& window, camera& cam, int score, int level, int lives,
              std::shared_ptr<stateManeger> manager);

    /**
     * @brief Waarschuwing dat er iets is veranderd in de score logica.
     * @param message De notificatie die is verzonden.
     */
    void notify(const logic::scoreViewNotifications& message) override;

    /**
     * @brief Tekent de score, level en levens op de juiste plaats in de window.
     */
    void draw() override;

    /**
     * @brief Schrijft de score weg naar een bestand als het spel is afgelopen.
     * @param score De score aan het einde van het spel.
     */
    static void gameEnded(int score);
};
} // view

#endif //PACKMAN_SCOREVIEW_H
