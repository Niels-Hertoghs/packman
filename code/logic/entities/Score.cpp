//
// Created by niels_hertoghs on 11/20/25.
//

#include "Score.h"

#include <cmath>

#include "../../view/ScoreView.h"
#include "../state_maneger/stateManeger.h"

namespace logic {
    Score::Score(stateManeger& Manager) : IObserver(),manager(Manager),  score(0),livesLeft(2),level(1) {}

    void Score::coinEaten(int coinPoints) {
        float lastEatenTime = Stopwatch::getInstance()->eatCollectable();
        // aantal coin points komt er bij de score als de collectable gegeten wordt na 1 sec
        // als het sneller wordt gedaan komen er meer punten bij, afhankelijk van hoe snel
        // (0.5 sec -> points verdubbeld, na 2 sec points gehalveerd)
        auto points = static_cast<float>(coinPoints);
        score += static_cast<int>(std::round(points/lastEatenTime));
        scoreObserver->notify(notifications::UPDATE_SCORE);
    }

    void Score::GhostEaten(int ghostPoints) {
        score += ghostPoints;
    }

    void Score::liveLost() {
        livesLeft--;
        scoreObserver->notify(notifications::UPDATE_LIVES);
        if (livesLeft < 0) {
            manager.prevState();
            scoreObserver->notify(notifications::END_GAME);
            std::unique_ptr<view::gameOverState> state = std::make_unique<view::gameOverState>();
            manager.pushState(std::move(state));
        }
    }

    void Score::nextLevel() {
        level++;
        scoreObserver->notify(notifications::UPDATE_LEVEL);
        std::unique_ptr<view::VictoryState> state = std::make_unique<view::VictoryState>();
        manager.pushStateAndDelete(std::move(state));
    }


    void Score::subscribeScore(std::shared_ptr<view::ScoreView> scoreView) {
        scoreObserver = std::move(scoreView);
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