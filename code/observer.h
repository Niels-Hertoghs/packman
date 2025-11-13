//
// Created by niels_hertoghs on 11/10/25.
//

#ifndef PACKMAN_OBSERVER_H
#define PACKMAN_OBSERVER_H
#include <SFML/Graphics.hpp>

#include "Stopwatch.h"
#include "render/notifications.h"
class IObserver {
};

class Observer {
protected:
    Stopwatch& stopwatch;
    sf::RenderWindow& window;
public:
    Observer(Stopwatch& stopwatch,sf::RenderWindow& window);
    virtual ~Observer() = default;

    virtual void notify(enum notifications message) = 0;
    virtual void draw() = 0;
};

class Score : public Observer {
private:
    int score;
public:
    Score(Stopwatch& stopwatch,sf::RenderWindow& window);
    void coinEaten(float coinPoints);
    virtual void notify(enum notifications message);

    [[nodiscard]] int getScore() const;
};


#endif //PACKMAN_OBSERVER_H