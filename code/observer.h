//
// Created by niels_hertoghs on 11/10/25.
//

#ifndef PACKMAN_OBSERVER_H
#define PACKMAN_OBSERVER_H
#include <SFML/Graphics.hpp>

#include "camera.h"
#include "Stopwatch.h"
#include "render/notifications.h"
class IObserver {
};

class Observer {
protected:
    Stopwatch& stopwatch;
    sf::RenderWindow& window;
    camera _camera;

public:
    Observer(Stopwatch& stopwatch,sf::RenderWindow& window,camera& camera);
    virtual ~Observer() = default;

    virtual void notify(enum notifications message) = 0;
    virtual void draw() = 0;
};

class Score : public Observer {
private:
    int score;
    sf::Font font;

public:
    Score(Stopwatch& stopwatch,sf::RenderWindow& window,camera& cam);
    void coinEaten(float coinPoints);
    void notify(enum notifications message) override;
    void draw() override;

    [[nodiscard]] int getScore() const;
};


#endif //PACKMAN_OBSERVER_H