//
// Created by niels_hertoghs on 11/20/25.
//

#include "Score.h"

#include "../../render/ScoreView.h"

namespace logic {
    Score::Score() : IObserver(), score(0),livesLeft(3),level(1) {}

    void Score::coinEaten(float coinPoints) {
        float lastEatenTime = Stopwatch::getInstance()->eatCollectable();
        // aantal coin points komt er bij de score als de collectable gegeten wordt na 1 sec
        // als het sneller wordt gedaan komen er meer punten bij, afhankelijk van hoe snel
        // (0.5 sec -> points verdubbeld, na 2 sec points gehalveerd)
        score += coinPoints/lastEatenTime;
        scoreObserver->notify(notifications::UPDATE_SCORE);
    }

    void Score::subscribeScore(std::shared_ptr<view::ScoreView> scoreView) {
        scoreObserver = scoreView;
    }

    int Score::getScore() const {
        return score;
    }

    int Score::getLivesLeft() const {
        return livesLeft;
    }

    int Score::getLevel() const {
        return level;
    }

} // logic