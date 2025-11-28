//
// Created by niels_hertoghs on 11/20/25.
//

#ifndef PACKMAN_SCORE_H
#define PACKMAN_SCORE_H
#include "../observer.h"



namespace view {
    class stateManeger;
    class ScoreView;
}

namespace logic {
    class Score : public IObserver {
    private:
        int score;
        int livesLeft;
        int level;
        std::shared_ptr<view::ScoreView> scoreObserver;
        view::stateManeger& manager;
    public:
        explicit Score( view::stateManeger& manager);
        void coinEaten(int coinPoints);
        void liveLost();
        void subscribeScore(std::shared_ptr<view::ScoreView> scoreView);
        void nextLevel();
        void GhostEaten(int GhostPoints);

        [[nodiscard]] int getScore() const;
        [[nodiscard]] int getLivesLeft() const;
        [[nodiscard]] int getLevel() const;
    };
} // logic

#endif //PACKMAN_SCORE_H