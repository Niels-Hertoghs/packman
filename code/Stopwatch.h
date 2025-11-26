//
// Created by niels_hertoghs on 11/8/25.
//

#ifndef PACKMAN_STOPWATCH_H
#define PACKMAN_STOPWATCH_H
#include <chrono>
#include <memory>
#include <set>
#include <utility>

/**
 * Class Stopwatch
 * brief Houdt alles van tijd bij in de game.
 */
class Stopwatch {
private:
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> startTime;
    std::chrono::time_point<clock> lastTime; /// tijdspunt van laatste tick
    std::chrono::time_point<clock> lastTimeEaten; /// tijdspunt van laatst gegeten coin
    std::chrono::time_point<clock> lastChangedSprite; /// tijdspunt van laatst veranderde sprite
    std::set<int> changedSprite; /// de Id's van de sprites die al veranderd zijn in de huidige frame

    float deltaTime; // in seconden

    Stopwatch(); // privat econstructor
    inline static std::shared_ptr<Stopwatch> _instance;
public:
    static std::shared_ptr<Stopwatch> getInstance();

    // Verwijder copy constructor en assignment operator, om singleton behouden
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    void tick();
    [[nodiscard]] float getDeltaTime() const;
    float eatCollectable();
    void reset();

    /**
     *
     * @return Ofdat de sprite moet veranderen.
     */
    bool changeSprite(int id);

    [[nodiscard]] bool canStartAfter5Sec() const;
    [[nodiscard]] bool canStartAfter10Sec() const;


    ~Stopwatch() = default;
};


#endif //PACKMAN_STOPWATCH_H