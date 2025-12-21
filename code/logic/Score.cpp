//
// Created by niels_hertoghs on 11/20/25.
//

#include "Score.h"
#include "Stopwatch.h"

namespace logic {
Score::Score()
    : Observer(), score(0), livesLeft(2), level(1) {
}

void Score::notify(const scoreNotifications& message) {
    switch (message.type) {
    case scoreNotificationsType::ENTITY_EATEN:
        if (message.isGhost) {
            // ghost heeft altijd een vaste score wanneer gegeten.
            score += message.points;
        } else {
            const float lastEatenTime = Stopwatch::getInstance()->eatCollectable();
            // aantal coin points komt er bij de score als de collectable gegeten wordt na 1 sec
            // als het sneller wordt gedaan komen er meer punten bij, afhankelijk van hoe snel
            // (0.5 sec -> points verdubbeld, na 2 sec points gehalveerd)
            const auto points = message.points;
            score += points / lastEatenTime;
        }
        notifyObservers(scoreViewTypes::UPDATE_SCORE);
        break;
    case scoreNotificationsType::LIVE_LOST: {
        livesLeft--;
        if (livesLeft < 0) {
            notifyObservers(scoreViewTypes::END_GAME);
        }
        notifyObservers(scoreViewTypes::UPDATE_LIVES);
        break;
    }
    case scoreNotificationsType::NEXT_lEVEL: {
        level++;
        score += 100; // Standaard extra punten voor het halen van een level
        notifyObservers(scoreViewTypes::UPDATE_LEVEL);
        break;
    }
    case scoreNotificationsType::DECREASE_SCORE: {
        score -= 10; // het aantal punten dat er van de score afgaan elke seconden.
        notifyObservers(scoreViewTypes::UPDATE_SCORE);
    }

    default:
        break;
    }
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

void Score::subscribe(std::shared_ptr<Observer<scoreViewNotifications>> observer) {
    observers.push_back(std::move(observer));
}

void Score::notifyObservers(const scoreViewTypes notification) const {
    scoreViewNotifications notif(notification);
    switch (notification) {
    case scoreViewTypes::UPDATE_SCORE:
        notif.score = score;
        break;
    case scoreViewTypes::UPDATE_LIVES:
        notif.lives = livesLeft;
        break;
    case scoreViewTypes::UPDATE_LEVEL:
        notif.level = level;
        break;
    case scoreViewTypes::END_GAME:
        notif.score = score;
    default:
        break;
    }
    for (const auto& observer : observers) {
        observer->notify(notif);
    }
}

void Score::reset() {
    score = 0;
    livesLeft = 2;
    level = 1;
    notifyObservers(scoreViewTypes::UPDATE_SCORE);
    notifyObservers(scoreViewTypes::UPDATE_LIVES);
}
} // logic
