//
// Created by niels_hertoghs on 11/10/25.
//

#include "observer.h"

Observer::Observer(Stopwatch& stopwatch,sf::RenderWindow& window2) : stopwatch(stopwatch),window(window2) {}

Score::Score(Stopwatch& stopwatch,sf::RenderWindow& window) : Observer(stopwatch,window), score(0) {}

void Score::coinEaten(float coinPoints) {
    float lastEatenTime = stopwatch.eatCollectable();
    // aantal coin points komt er bij de score als de collectable gegeten wordt na 1 sec
    // als het sneller wordt gedaan komen er meer punten bij, afhankelijk van hoe snel
    // (0.5 sec -> points verdubbeld, na 2 sec points gehalveerd)
    score += coinPoints/lastEatenTime;
}

int Score::getScore() const {
    return score;
}


