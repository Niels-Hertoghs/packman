//
// Created by niels_hertoghs on 11/20/25.
//

#ifndef PACKMAN_SCOREVIEW_H
#define PACKMAN_SCOREVIEW_H
#include "observerView.h"
#include "../logic/Score.h"

namespace view {
    /**
     * @class ScoreView
     * @brief Concrete klasse voor de score observer.
     */
    class ScoreView final : public ObserverView<scoreViewNotifications> {
        sf::Font font;  /// Font voor de score tekst.
        std::weak_ptr<logic::Score> scoreModel; /// Pointer naar de logica van de score.
        sf::Text scoreText; /// Tekst voor de score.
        sf::Text levelText; /// Tekst voor het level.
        sf::Text livesText; /// Tekst voor het aantal levens.
    public:
        /**
         * @brief Constructor
         * @param window Waar het op moet worden afgebeeld.
         * @param cam Camera klasse voor het omzetten naar pixel coordinaten.
         * @param Score Pointer naar de logica van de score.
         */
        ScoreView(sf::RenderWindow& window,camera& cam,std::shared_ptr<logic::Score>& Score);

        /**
         * @brief Waarschuwing dat er iets is veranderd in de score logica.
         * @param message De notificatie die is verzonden.
         */
        void notify(const notifications& message) override;

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