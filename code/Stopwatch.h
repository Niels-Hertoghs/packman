//
// Created by niels_hertoghs on 11/8/25.
//

#ifndef PACKMAN_STOPWATCH_H
#define PACKMAN_STOPWATCH_H
#include <chrono>

/**
 * Class Stopwatch
 * brief Houdt alles van tijd bij in de game.
 */
class Stopwatch {
private:
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> lastTime; /// tijdspunt van laatste tick
    std::chrono::time_point<clock> lastTimeEaten; /// tijdspunt van laatst gegeten coin
    std::chrono::time_point<clock> lastChangedSprite; /// tijdspunt van laatst veranderede sprite
    float deltaTime; // in seconden

    Stopwatch(); // privat econstructor
public:
    static Stopwatch& getInstance();

    // Verwijder copy constructor en assignment operator, om singleton behouden
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    void tick();
    float getDeltaTime() const;
    float eatCollectable();

    /**
     *
     * @return Ofdat de sprite moet veranderen.
     */
    bool changeSprite();

    ~Stopwatch() = default;
};


#endif //PACKMAN_STOPWATCH_H