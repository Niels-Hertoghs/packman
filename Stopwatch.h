//
// Created by niels_hertoghs on 11/8/25.
//

#ifndef PACKMAN_STOPWATCH_H
#define PACKMAN_STOPWATCH_H
#include <chrono>


class Stopwatch {
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> lastTime;
    float deltaTime; // in seconden
public:
    Stopwatch();

    void tick();
    float getDeltaTime() const;
};


#endif //PACKMAN_STOPWATCH_H