//
// Created by niels_hertoghs on 11/20/25.
//

#ifndef PACKMAN_SCORE_H
#define PACKMAN_SCORE_H
#include "../../observer.h"

class stateManeger;

namespace view {
    class ScoreView;
}

namespace logic {
    class Score : public IObserver {
    private:
        int score;
        int livesLeft;
        int level;
        std::shared_ptr<view::ScoreView> scoreObserver;
        stateManeger& manager;
    public:
        explicit Score(stateManeger& manager);
        void coinEaten(int coinPoints);
        void liveLost();
        void subscribeScore(std::shared_ptr<view::ScoreView> scoreView);
        void nextLevel();

        [[nodiscard]] int getScore() const;
        [[nodiscard]] int getLivesLeft() const;
        [[nodiscard]] int getLevel() const;
    };
} // logic

#endif //PACKMAN_SCORE_H