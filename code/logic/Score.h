//
// Created by niels_hertoghs on 11/20/25.
//

#ifndef PACKMAN_SCORE_H
#define PACKMAN_SCORE_H
#include <memory>

#include "../observer.h"

// Forward declarations
namespace view {
    class stateManeger;
    class ScoreView;
}

namespace logic {
    /**
     * @class Score
     * @brief Klasse die de score, levens en level bijhoudt.
     */
    class Score : public IObserver {
        int score;  /// de huidige score van de speler.
        int livesLeft; /// Het aantal levens dat de speler nog over heeft.
        int level; /// Het huidige level van de speler.
        std::shared_ptr<view::ScoreView> scoreObserver;  /// Pointer naar de score observer.
        view::stateManeger& manager; /// Reference naar de state manager, om states te kunnen veranderen bij game over of level up.
    public:
        /**
         * @brief Constructor voor de score.
         * @param manager Reference naar de state manager, om states te kunnen veranderen bij game over of level up.
         */
        explicit Score( view::stateManeger& manager);

        /**
         * @brief Voegt punten toe aan de score als een coin of fruit is opgegeten.
         * @param coinPoints Het aantal punten dat de coin waard is.
         */
        void coinEaten(int coinPoints);

        /**
         * @brief Wordt opgeroepen als de speler een leven verliest, verminderd het aantal levens en checkt voor game over.
         */
        void liveLost();

        /**
         * @brief Laat de score view observer subscriben aan de score.
         * @param scoreView Pointer naar de score view observer om te subscriben.
         */
        void subscribeScore(std::shared_ptr<view::ScoreView> scoreView);

        /**
         * @brief Gaat baar het volgende level, verhoogt het level en verandert de state naar de victory state.
         */
        void nextLevel();

        /**
         * @brief Voegt punten toe aan de score als een ghost is opgegeten.
         * @param GhostPoints Het aantal punten dat de ghost waard is.
         */
        void GhostEaten(int GhostPoints);

        // getters
        /**
         * @return De huidige score van de speler.
         */
        [[nodiscard]] int getScore() const;

        /**
         * @return Het aantal levens dat de speler nog over heeft.
         */
        [[nodiscard]] int getLivesLeft() const;

        /**
         * @return Het huidige level van de speler.
         */
        [[nodiscard]] int getLevel() const;

        /**
         * @brief Default destructor.
         */
        ~Score() override = default;
    };
} // logic

#endif //PACKMAN_SCORE_H