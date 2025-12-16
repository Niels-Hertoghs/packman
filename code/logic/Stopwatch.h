//
// Created by niels_hertoghs on 11/8/25.
//

#ifndef PACKMAN_STOPWATCH_H
#define PACKMAN_STOPWATCH_H
#include <chrono>
#include <memory>
#include <set>
#include <utility>

namespace logic {
    /**
     * @Class Stopwatch
     * @brief Houdt alles van tijd bij in de game.
     */
    class Stopwatch {
        using clock = std::chrono::high_resolution_clock; /// Afkorten naar clock.
        std::chrono::time_point<clock> startTime; /// Tijdspunt dat de game is gestart.
        std::chrono::time_point<clock> lastTime; /// Tijdspunt van laatste tick.
        std::chrono::time_point<clock> lastTimeEaten; /// Tijdspunt van laatst gegeten coin.
        std::chrono::time_point<clock> lastChangedSprite; /// Tijdspunt van laatst veranderde sprite.
        std::chrono::time_point<clock> _startFearMode; /// Start tijdspunt vn fear mode.
        std::set<int> changedSprite; /// De Id's van de sprites die al veranderd zijn in de huidige frame.
        float deltaTime; /// Tijd tussen 2 updates
        Stopwatch(); /// private constructor (singleton)
        inline static std::shared_ptr<Stopwatch> _instance; /// Pointer naar singleton.
    public:
        /**
        * @return De enige instantie van de random klasse (pointer).
        */
        static std::shared_ptr<Stopwatch> getInstance();

        // Verwijder copy constructor en assignment operator, om singleton behouden
        Stopwatch(const Stopwatch &) = delete;

        Stopwatch &operator=(const Stopwatch &) = delete;

        /**
         * @brief Als er een nieuwe update gedaan wordt, past deltaTime aan.
         */
        void tick();

        /**
         * @return De tijd tussen twee updates, delta time.
         */
        [[nodiscard]] float getDeltaTime() const;

        /**
         * @return De tijd tussen de vorige en het net gegeten collectable.
         */
        [[nodiscard]] float eatCollectable();

        /**
         * @brief Reset alle tijdselementen. Voor als de player dood gaat of als er een nieuw level wordt gestart.
         */
        void reset();

        /**
         * @return Ofdat de sprite moet veranderen tijdens de update (1 keer per update).
         */
        [[nodiscard]] bool changeSprite(int id);

        /**
         * @return Of dat het spel al 5 sec of langer bezig is, dan mag er een ghost vertrekken.
         */
        [[nodiscard]] bool canStartAfter5Sec() const;

        /**
        * @return Of dat het spel al 10 sec of langer bezig is, dan mag er een ghost vertrekken.
        */
        [[nodiscard]] bool canStartAfter10Sec() const;

        /**
         * @brief Als fear mode start in het spel.
         */
        void startFearMode();

        /**
         * @brief Berekent of fear mode gedaan is afhankelijk van het level.
         * @param level Het huidige level, beinvloedt de lengte van de fear mode.
         * @return Bool, of dat fear mode gedaan is
         */
        [[nodiscard]] bool isFearDone(int level) const;

        /**
         * @brief Default destructor.
         */
        ~Stopwatch() = default;
    };
}


#endif //PACKMAN_STOPWATCH_H