//
// Created by niels_hertoghs on 11/10/25.
//

#ifndef PACKMAN_OBSERVER_H
#define PACKMAN_OBSERVER_H
#include "Stopwatch.h"


class Observer {
protected:
    Stopwatch& stopwatch;
public:
    Observer(Stopwatch& stopwatch);
};

class Score : public Observer {
private:
    int score;
public:
    Score(Stopwatch& stopwatch);
    void coinEaten(float coinPoints);

    [[nodiscard]] int getScore() const;
};


#endif //PACKMAN_OBSERVER_H