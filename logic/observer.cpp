//
// Created by niels_hertoghs on 11/10/25.
//

#include "observer.h"

Observer::Observer(Stopwatch& stopwatch) : stopwatch(stopwatch) {}

Score::Score(Stopwatch& stopwatch) : Observer(stopwatch), score(0) {}

void Score::coinEaten() {
    score += 100;
}

int Score::getScore() const {
    return score;
}


